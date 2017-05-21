#include "../Potentiostat.h"
#include "../ComPacket.h"

extern uint64_t getNow();

Potentiostat pstat;
DACBuffer_t DACBuf1;
ADCBuffer_t ADCBuf1;

void setup() {
	Serial.begin(9600);
	pstat.init(&DACBuf1, &DACBuf1, &ADCBuf1, &ADCBuf1);

	ExperimentNode_t exp[3];

	exp[0].isHead = true;
	exp[0].nodeType = DCNODE_SWEEP;
	exp[0].tMin = 100000;
	exp[0].tMax = 10000000000;
	exp[0].samplingParams.ADCTimerDiv = 2;
	exp[0].samplingParams.ADCTimerPeriod = 15625;
	exp[0].samplingParams.ADCBufferSize = 20;
	exp[0].samplingParams.DACMultiplier = 20;
	exp[0].DCSweep.VStart = 0;
	exp[0].DCSweep.VEnd = 1024;
	exp[0].DCSweep.dVdt = 1;

	exp[1].isTail = true;
	exp[1].nodeType = DCNODE_SWEEP;
	exp[1].tMin = 100000;
	exp[1].tMax = 100000000;
	exp[1].samplingParams.ADCTimerDiv = 2;
	exp[1].samplingParams.ADCTimerPeriod = 15625;
	exp[1].samplingParams.ADCBufferSize = 20;
	exp[1].samplingParams.DACMultiplier = 20;
	exp[1].DCSweep.VStart = 1024;
	exp[1].DCSweep.VEnd = 0;
	exp[1].DCSweep.dVdt = -1;
	exp[1].MaxPlays = 3;
	exp[1].branchHeadIndex = 0;
	memcpy((char *)pstat.getExperimentNodesPointer(),(char*)&exp[0], sizeof(ExperimentNode_t)*3);
}

void loop() {
	if (Serial.available() >= HEADER_LENGTH)
	{
		if (Serial.read() == FRAMING_LBYTE && Serial.peek() == FRAMING_UBYTE)
		{
			Serial.read();				//get FRAMING_UBYTE out of the queue
			volatile FramelessComPacketHeader_t packet;
			Serial.readBytes((char *)&packet, sizeof(packet));
			switch (packet.command)
			{
				case HANDSHAKE:
				{
					FramedComPacketHeader_t transmission;
					transmission.returnCode = HANDSHAKE_RESPONSE;
					transmission.channelNum = pstat.channelNum;
					transmission.dataLength = 0;
					Serial.write((char *)&transmission, sizeof(transmission));
				}
					break;
				case REPORT_STATUS:
					//TODO
					break;
				case SEND_CAL_DATA:
				{
					FramedComPacketHeader_t transmission;
					transmission.channelNum = pstat.channelNum;
					transmission.returnCode = CAL_DATA;
					transmission.dataLength = sizeof(pstat.cal);
					Serial.write((char *)&transmission, sizeof(transmission));
					Serial.write((char *)&pstat.cal, sizeof(pstat.cal));
				}
					break;
				case DOWNLOAD_EXPERIMENT:
				{
					Serial.readBytes((char *)pstat.getExperimentNodesPointer(), packet.dataLength);
					//FunctionToStop();
				}
					break;
				case RUN_EXPERIMENT:
				{
        //memcpy((char *)pstat.getExperimentNodesPointer(),(char*)&exp[0], sizeof(ExperimentNode_t)*3);
					pstat.runExperiment(getNow());
				}
				break;
				case SET_OPMODE:
					//TODO
					break;
				case MANUAL_DC_SAMPLE:
					//TODO
					break;
				case V_SETPOINT:
					//TODO
					break;
				case I_SETPOINT:
					//TODO
					break;
				case SETUP_AC_SAMPLING:
					//TODO
					break;
				case RUN_FRA:
					//TODO
					break;
				default:
					break;
			}
		}
	}

	if (pstat.status == DC_NODE_ACTIVE)
	{
		pstat.updateDummyStates(getNow());
		if (pstat.isCurrentNodeFinished(getNow()))
		{
			InstrStatus_t stat = pstat.initNextNode(getNow());
			if (stat == EXPERIMENT_COMPLETED)
			{
				FramedComPacketHeader_t transmission;
				transmission.channelNum = pstat.channelNum;
				transmission.returnCode = EXPERIMENT_COMPLETE;
				transmission.dataLength = 0;
				Serial.write((char *)&transmission, sizeof(transmission));
			}
		}
	}
 //*/
	//TODO: poll overcurrent, overvoltage
}

uint64_t getNow()
{
	return 100 * ((uint64_t)millis() * 1000 + (uint64_t)micros() % 1000);
}
