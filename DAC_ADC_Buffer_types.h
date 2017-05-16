#ifndef DAC_ADC_BUFFER_TYPES_H
#define DAC_ADC_BUFFER_TYPES_H

#include "global_typedefs.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
    
#include <stdbool.h>
#include <stdint.h>

    typedef struct {
        uint16_t associatedExperimentNode;
        uint16_t dataIndex;
        bool isEmpty;
        int16_t buf[DACBUF_SIZE];
    }DACBuffer_t;

#pragma pack(push, 1)
    typedef struct
    {
        uint16_t ref;
        uint16_t ewe;
        uint16_t current;
        uint16_t ece;
    }ADCdc_datastruct_t;
#pragma pack(pop)
    
    typedef struct
    {
        int16_t dataIndex;
        int16_t numIgnoredPoints;
        bool isFull;
        bool isActive;
        ADCdc_datastruct_t buf[ADCBUF_SIZE];
        uint64_t timeData[ADCBUF_SIZE];
    }ADCBuffer_t;
    
    
    
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* DAC_ADC_BUFFER_TYPES_H */

