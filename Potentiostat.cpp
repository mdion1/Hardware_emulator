#include "Potentiostat.h"
#include "Arduino.h"

Potentiostat::Potentiostat() {}
Potentiostat::Potentiostat(const Potentiostat& orig) {}
Potentiostat::~Potentiostat() {}

void * Potentiostat::getExperimentNodesPointer()
{
	return (void *)&experiment.nodes[0];
}

void Potentiostat::runExperiment(uint64_t tNow)
{
	uint16_t i = 0;
	while (experiment.nodes[i].nodeType != END_EXPERIMENT_NODE)
	{
		experiment.nodes[i].numPlays = 0;
		i++;
	}

	last_tSample = tNow;
	experiment.initNode(0, tNow);
	status = DC_NODE_ACTIVE;
}

void Potentiostat::init(DACBuffer_t * DACBuf1, DACBuffer_t * DACBuf2, ADCBuffer_t * ADCBuf1, ADCBuffer_t * ADCBuf2)
{
  status = IDLE;
	DACdcActiveBuf = DACBuf1;
	DACdcInactiveBuf = DACBuf2;
	ADCdcActiveBuf = ADCBuf1;
	ADCdcInactiveBuf = ADCBuf2;
}

InstrStatus_t Potentiostat::initNextNode(uint64_t tNow)
{
	return (status = experiment.initNode(experiment.SeekNextNode(), tNow));
}

void Potentiostat::updateDummyStates(uint64_t tNow)
{
	ExperimentNode_t * pNode = &experiment.nodes[experiment.nodeIndex];
	uint16_t divider = timeDivFactors[pNode->samplingParams.ADCTimerDiv];
	uint32_t interval = pNode->samplingParams.ADCTimerPeriod * divider;

	if (tNow >= interval + last_tSample)
	{
		//Serial.println((unsigned int)tNow); //Serial.print(','); Serial.println((unsigned int)last_tSample);
		last_tSample += interval;
		ADCdcActiveBuf->dataIndex++;
		if (ADCdcActiveBuf->dataIndex >= pNode->samplingParams.ADCBufferSize)
		{
			ADCdcActiveBuf->dataIndex = 0;
			ADCdc_data_now.current = currentFormula(DCVctrl);
			currentRange = currentRangeFormula(DCVctrl);
			ADCdc_data_now.ewe = DCVctrl;
			ADCdc_data_now.ref = 0;
			ADCdc_data_now.ece = -DCVctrl / 2;

			/* Send transmission */
			timestamp = tNow;
			FramedComPacketHeader_t transmission;
			transmission.channelNum = channelNum;
			transmission.returnCode = ADCDC_DATA;
			transmission.dataLength = 4 * 2 + 1 + 8;
			uint8_t data[4 * 2 + 1 + 8];
			memcpy(data, (uint8_t *)&ADCdc_data_now, 4 * 2);
			memcpy(&data[4 * 2], (uint8_t *)&currentRange, 1);
			memcpy(&data[4 * 2 + 1], (uint8_t *)&timestamp, 8);
			Serial.write((uint8_t *)&transmission, sizeof(transmission));
			Serial.write(data, sizeof(data));
			//Serial.println(ADCdc_data_now.ewe);   //debugging
		}

		if (++ADCdcActiveBuf->DACcounter >= pNode->samplingParams.DACMultiplier)
		{
			ADCdcActiveBuf->DACcounter = 0;
			DCVctrl = updateDummyVCtrl(tNow);
		}
	}
}

int16_t Potentiostat::updateDummyVCtrl(uint64_t tNow)
{
	uint16_t retVal = DCVctrl;
	ExperimentNode_t * pNode = &experiment.nodes[experiment.nodeIndex];
	switch (pNode->nodeType)
	{
		case DCNODE_POINT:
		{
			retVal = pNode->DCPoint.VPoint;
		}
		break;
		case DCNODE_SWEEP:
		{
			if (pNode->DCSweep.dVdt > 0)
				retVal = DCVctrl + 1;
			else
				retVal = DCVctrl - 1;
		}
		break;
		case DCNODE_NORMALPULSE:
		{
			if (pNode->DCPulseNormal.evenOdd ^= 1)
			{
				retVal = pNode->DCPulseNormal.VStart;
			}
			else
			{
				retVal = pNode->DCPulseNormal.VInitHeight;
				pNode->DCPulseNormal.VInitHeight += pNode->DCPulseNormal.VStep;
			}
		}
		break;
		case DCNODE_DIFFPULSE:
		{
			if (pNode->DCPulseDiff.evenOdd ^= 1)
			{
				retVal = pNode->DCPulseDiff.VStart;
				pNode->DCPulseDiff.VStart += pNode->DCPulseDiff.VStep;
			}
			else
			{
				retVal = pNode->DCPulseDiff.VStart + pNode->DCPulseDiff.VHeight;
			}
		}
		break;
		case DCNODE_SQRWAVE:
		{
			if (pNode->DCSqrWave.evenOdd ^= 1)
			{
				retVal = pNode->DCSqrWave.VCenter + pNode->DCSqrWave.VAmp;
			}
			else
			{
				retVal = pNode->DCSqrWave.VCenter - pNode->DCSqrWave.VAmp;
			}
		}
		break;
		case DCNODE_SINEWAVE:
			//TODO
		case ACNODE_POTENTIOSTATIC:
			//TODO
		case ACNODE_GALVANOSTATIC:
			//TODO
		case ACNODE_HYBRID:
			//TODO
		case DCNODE_OCP:
		default:
			break;
	}
	return retVal;
}

bool Potentiostat::isCurrentNodeFinished(uint64_t tNow)
{
	bool retVal = false;
	ExperimentNode_t * pNode = &experiment.nodes[experiment.nodeIndex];
	switch (pNode->nodeType)
	{
		case DCNODE_OCP:
		case DCNODE_POINT:
		case DCNODE_NORMALPULSE:
		case DCNODE_DIFFPULSE:
		case DCNODE_SQRWAVE:
		case DCNODE_SINEWAVE:
		{
			if (tNow - pNode->t_start >= pNode->tMax)
				retVal = true;
		}
		break;
		case DCNODE_SWEEP:
		{
			if ((pNode->DCSweep.dVdt > 0 && DCVctrl >= pNode->DCSweep.VEnd) ||
				(pNode->DCSweep.dVdt < 0 && DCVctrl <= pNode->DCSweep.VEnd))
				retVal = true;
		}
		break;
		
		case ACNODE_POTENTIOSTATIC:
			//TODO
		case ACNODE_GALVANOSTATIC:
			//TODO
		case ACNODE_HYBRID:
			//TODO
		default:
			break;
	}
	return retVal;
}

int16_t Potentiostat::currentFormula(int16_t DAC)
{
	return DAC;
}

currentRange_t Potentiostat::currentRangeFormula(int16_t DAC)
{
	return RANGE0;
}
// </editor-fold>
