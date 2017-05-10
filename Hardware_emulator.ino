#include "Potentiostat.h"
#include "ComPacket.h"

Potentiostat pstat;

void setup() {
	Serial.begin(9600);

}

void loop() {
	if (Serial.available() >= HEADER_LENGTH)
	{
		if (Serial.read() == FRAMING_UBYTE && Serial.peek() == FRAMING_LBYTE)
		{
			Serial.read();				//get FRAMING_LBYTE out of the queue
			FramelessComPacketHeader_t packet;
			Serial.readBytes((uint8_t *)&packet, sizeof(packet));
			switch (packet.command)
			{
				case HANDSHAKE:
				{
					FramedComPacketHeader_t transmission;
					transmission.returnCode = HANDSHAKE;
					Serial.write((uint8_t *)&transmission, sizeof(transmission));
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
					Serial.write((uint8_t *)&transmission, sizeof(transmission));
					Serial.write((uint8_t *)&pstat.cal, sizeof(pstat.cal));
				}
					break;
				case DOWNLOAD_EXPERIMENT:
				{
					Serial.readBytes((uint8_t *)&pstat.experiment.nodes, packet.dataLength);
				}
					break;
				case RUN_EXPERIMENT:
				{
					pstat.runExperiment();
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
		if (pstat.updateDummyStates() == ADCDATA_READY)
		{
			FramedComPacketHeader_t transmission;
			transmission.returnCode = ADCDC_DATA;
			transmission.dataLength = 4 * 2 + 1 + 8;
			uint8_t data[4 * 2 + 1 + 8];
			memcpy(data, (uint8_t *) &pstat.ADCdc_data_now, 4 * 2);
			memcpy(&data[4 * 2], (uint8_t *)&pstat.currentRange, 1);
			memcpy(&data[4 * 2 + 1], (uint8_t *)&pstat.timestamp, 8);
			Serial.write((uint8_t *)&transmission, sizeof(transmission));
		}
		pstat.updateDummyVCtrl();
		if (pstat.isCurrentNodeFinished())
		{
			status_t stat = pstat.initNextNode();
			if (stat == EXPERIMENT_COMPLETED)
			{
				FramedComPacketHeader_t transmission;
				transmission.returnCode = EXPERIMENT_COMPLETE;
				Serial.write((uint8_t *)&transmission, sizeof(transmission));
			}
		}
	}

}
