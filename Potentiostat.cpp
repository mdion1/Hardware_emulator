#include "Potentiostat.h"

Potentiostat::Potentiostat() {
}

Potentiostat::Potentiostat(const Potentiostat& orig) {
}

Potentiostat::~Potentiostat() {}

void Potentiostat::runExperiment()
{
	experiment.initNode(0);
}

void Potentiostat::updateDummyVCtrl(uint32_t tNow)
{
	ExperimentNode_t * pNode = &experiment.nodes[experiment.nodeIndex];
	switch (pNode->nodeType)
	{
		case DCNODE_POINT:
		{
			DCVctrl = pNode->DCPoint.VPoint;
		}
		break;
		case DCNODE_SWEEP:
		{
			if (pNode->DCSweep.dVdt > 0)
				DCVctrl++;
			else
				DCVctrl--;
		}
		break;
		case DCNODE_NORMALPULSE:
		{
			//TODO
		}
		break;
		case DCNODE_DIFFPULSE:
		{
			//TODO
		}
		break;
		case DCNODE_SQRWAVE:
		{
			//TODO
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
		case DCNODE_POINT:
		default:
			break;
	}
}

void Potentiostat::isCurrentNodeFinished(uint64_t tNow)
{
	
}


void Potentiostat::updateDummyStates(uint32_t tNow)
{
	status_t returnVal = CHANNEL_ERROR;

	ExperimentNode_t * pNode = &experiment.nodes[experiment.nodeIndex];
	uint8_t divider = timeDivFactors[pNode->samplingParams.ADCTimerDiv];
	uint32_t interval = pNode->samplingParams.ADCTimerPeriod * divider / 100;
	if (tNow - pstat.last_tSample >= interval)
	{
		pstat.last_tSample += interval;
		if (++pstat.ADCdcActiveBuf->dataIndex >= pNode->samplingParams.DACMultiplier)
		{
			pstat.ADCdc_data_now.current = ? ? ;
			pstat.ADCdc_data_now.ewe = DACvalue;
			pstat.ADCdc_data_now.ref = 0;
			pstat.ADCdc_data_now.ece = -DACvalue / 2;
			returnVal = ADCDATA_READY;
			//increment DAC data;
		}

	}
}
// </editor-fold>