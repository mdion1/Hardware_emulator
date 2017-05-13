#include "Potentiostat.h"
#include "ComPacket.h"

Potentiostat pstat;
DACBuffer_t DACBuf1;
ADCBuffer_t ADCBuf1;

void setup() {
	Serial.begin(9600);
	pstat.init(&DACBuf1, &DACBuf1, &ADCBuf1, &ADCBuf1);
}

void loop() {
	if (Serial.available() >= HEADER_LENGTH)
	{
		if (Serial.read() == FRAMING_UBYTE && Serial.peek() == FRAMING_LBYTE)
		{
			Serial.read();				//get FRAMING_LBYTE out of the queue
			FramelessComPacketHeader_t packet;
			Serial.readBytes((char *)&packet, sizeof(packet));
			switch (packet.command)
			{
				case HANDSHAKE:
				{
					FramedComPacketHeader_t transmission;
					transmission.returnCode = HANDSHAKE_RESPONSE;
					Serial.write((char *)&transmission, sizeof(transmission));
				}
					break;
				case REPORT_STATUS:
					//TODO
					break;
				case SEND_CAL_DATA:
				{
					FramedComPacketHeader_t transmission;
					transmission.returnCode = CAL_DATA;
					transmission.dataLength = sizeof(pstat.cal);
					Serial.write((char *)&transmission, sizeof(transmission));
					Serial.write((char *)&pstat.cal, sizeof(pstat.cal));
				}
					break;
				case DOWNLOAD_EXPERIMENT:
				{
					Serial.readBytes((char *)pstat.getExperimentNodesPointer(), packet.dataLength);
				}
					break;
				case RUN_EXPERIMENT:
				{
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
				transmission.returnCode = EXPERIMENT_COMPLETE;
				Serial.write((char *)&transmission, sizeof(transmission));
			}
		}
	}
	//TODO: poll overcurrent, overvoltage
}

uint64_t getNow()
{
	return 100 * (millis() * 1000 + micros() % 1000);
}
