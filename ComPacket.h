#ifndef COM_PACKET_H
#define COM_PACKET_H

typedef struct
{
	PCcommand_t command;
	uint8_t channelNum;
	uint16_t dataLength;
}FramelessComPacketHeader_t;

typedef struct
{
	uint16_t frame = 0xFFEE;
	Notifications_t returnCode;
	uint8_t channelNum;
	uint16_t dataLength;
}FramedComPacketHeader_t;

#endif