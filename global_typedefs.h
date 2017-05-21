#ifndef _GLOBAL_TYPEDEFS_H    /* Guard against multiple inclusion */
#define _GLOBAL_TYPEDEFS_H

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

	/* Definitions */
#define ABS(x) (x > 0 ? x : -x)
#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x < y ? x : y)
#define OVERCURRENT_LIMIT 32700
#define UNDERCURRENT_LIMIT 2500
#define OVERCURRENT_MAX_COUNT 1000
#define UNDERCURRENT_MAX_COUNT 1000
#define OVERVOLTAGE_LIMIT 32700
#define DACBUF_SIZE 128 
#define ADCBUF_SIZE 128

#define HEADER_LENGTH 5
#define FRAMING_UBYTE 0xFF
#define FRAMING_LBYTE 0xEE
#define FRAMING_WORD 0xFFEE
//#define FRAMING_UBYTE 65
//#define FRAMING_LBYTE 65

	const uint16_t timeDivFactors[] = {1, 2, 4, 8, 16, 32, 64, 256};
    
    /* Typedef enums*/
typedef enum : unsigned char {
	HANDSHAKE = 65,
    REPORT_STATUS,
    SEND_CAL_DATA,
    SET_OPMODE,
    MANUAL_DC_SAMPLE,
    V_SETPOINT,
    I_SETPOINT,
    SETUP_AC_SAMPLING,
    RUN_FRA,
	DOWNLOAD_EXPERIMENT,
	RUN_EXPERIMENT
}PCcommand_t;

typedef enum : unsigned char {
	CHANNEL_OK,
	ECE_OVERVOLTAGE_WARNING,
	EWE_OVERVOLTAGE_WARNING,
	REF_OVERVOLTAGE_WARNING,
	OVERCURRENT_WARNING,
	UNDERCURRENT_WARNING,
	HANDSHAKE_RESPONSE = 65,
	ADCDC_DATA,
	ADCAC_DATA,
	CAL_DATA,
	ERROR_MSG,
	STATUS_DATA,
	EXPERIMENT_COMPLETE
}Notifications_t;

typedef enum {
	INITIALIZING, IDLE, OCP, DC_NODE_ACTIVE, AC_NODE_ACTIVE, CHANNEL_ERROR, EXPERIMENT_COMPLETED
}InstrStatus_t;

typedef enum {USB_STATE_DEVICE_LAYER_UNOPENED,
        USB_STATE_UNPOWERED,
        USB_STATE_DEVICE_LAYER_POWERED_DETACHED,
        USB_STATE_POWERED_ATTACHED_UNCONFIGURED,
        USB_STATE_CDC_CONFIGURED,
        USB_STATE_DEVICE_LAYER_ERROR
}USBstate_t;

typedef enum {USBSERIAL_READ_STATUS_COMPLETE,
        USBSERIAL_READ_STATUS_PENDING,
        USBSERIAL_READ_STATUS_ERROR
}USBSerialReadState_t;

typedef enum {USBSERIAL_WRITE_STATUS_COMPLETE,
        USBSERIAL_WRITE_STATUS_PENDING,
        USBSERIAL_WRITE_STATUS_ERROR
}USBSerialWriteState_t;

typedef enum {POTENTIOSTATIC, GALVANOSTATIC}opmode_t;

typedef enum : int8_t {OFF = -1, RANGE0, RANGE1, RANGE2, RANGE3, RANGE4, RANGE5, RANGE6, RANGE7
}currentRange_t;

typedef enum {CURRENT_AUTORANGE, CURRENT_MANUAL_RANGE}currentRangeMode_t;

typedef enum : unsigned char {
	DCNODE_OCP, //TODO: add potentiostatic vs galvanostatic distinctions
    DCNODE_SWEEP,
    DCNODE_POINT,
    DCNODE_NORMALPULSE,
    DCNODE_DIFFPULSE,
    DCNODE_SQRWAVE,
    DCNODE_SINEWAVE,
    ACNODE_POTENTIOSTATIC,
    ACNODE_GALVANOSTATIC,
    ACNODE_HYBRID,
    END_EXPERIMENT_NODE
}NodeType_t;

typedef enum {AC_GAIN1, AC_GAIN2, AC_GAIN5, AC_GAIN10
}ACgain_t;

typedef enum {HF_RANGE, LF_RANGE
}freq_range_t;

typedef enum : unsigned char {
        WAVEGENCLK_25MHZ = 1,
        WAVEGENCLK_12_5MHZ = 2,
        WAVEGENCLK_6_25MHZ = 4,
        WAVEGENCLK_3_125MHZ = 8,
        WAVEGENCLK_1_5625MHZ = 16,
        WAVEGENCLK_0_78125MHZ = 32
    }WAVEGENCLK_SPEED_t; 
    
typedef enum{SPI_MODE0 = 0, SPI_MODE1, SPI_MODE2, SPI_MODE3}SPI_MODE_t;
typedef enum{SPI_50M_BAUD, SPI_25M_BAUD, SPI_10M_BAUD, SPI_5M_BAUD, SPI_1M_BAUD}SPI_BAUDRATE_t;
typedef enum{SPI_8BITS, SPI_16BITS, SPI_32BITS}SPI_TX_LENGTH_t;

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _GLOBAL_H */
