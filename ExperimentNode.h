#ifndef EXPERIMENT_NODE_H
#define EXPERIMENT_NODE_H

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
    
#include <stdint.h>
#include <stdbool.h>
#include "global_typedefs.h"

#pragma pack(push, 4)

typedef struct
{
    NodeType_t nodeType;
    bool isHead;
    bool isTail;
    uint16_t branchHeadIndex;
    uint32_t MaxPlays;
    uint32_t numPlays;
    uint64_t t_start;
    uint64_t tMin;
    uint64_t tMax;
    bool BufOverflowFlag;
    
    struct
    {
        uint8_t ADCTimerDiv;
        uint32_t ADCTimerPeriod;
        uint16_t ADCBufferSize;
        bool isDACStatic;
        uint16_t DACMultiplier;
        uint16_t PointsIgnored;
    }samplingParams;
    
    union
    { 
        /* Experiment_End_Node */
        struct
        {
        }ExperimentEndNode;
        
        /* DCNode_OCP */
        struct
        {   
            uint32_t t_interval;
            int16_t Vmin;
            int16_t Vmax;
            float dVdtMax;
        }DCocp;
        
        /* DCNode_Sweep */
        struct
        {
            uint32_t t_interval;
            int16_t VStart;
            int16_t VEnd;
            float Imax;
            float Imin;
            float dVdt;
        }DCSweep;
        
        /* DCNode_Point */
        struct
        {
            int16_t VPoint;
            int16_t Imax;
            int16_t Imin;
            currentRange_t IrangeMax;
            currentRange_t IrangeMin;
        }DCPoint;
        
        /* DCNode_NormalPulse */
        struct
        {
            int16_t VStart;
            float VStep;
            int16_t VEnd;
            int16_t VInitHeight;
            uint32_t t_pulse;
            uint32_t t_period;
			bool evenOdd;
        }DCPulseNormal;
        
        /* DCNode_DiffPulse */
        struct
        {
            int16_t VStart;
            float VStep;
            int16_t VHeight;
            int16_t VEnd;
            uint32_t t_pulse;
            uint32_t t_period;
			bool evenOdd;
        }DCPulseDiff;
        
        /* DCNode_SqrWave */
        struct
        {
            uint32_t t_interval;
            int16_t VCenter;
            int16_t VAmp;
            uint32_t t_period;
			bool evenOdd;
        }DCSqrWave;
        
        /* DCNode_SineWave */
        struct
        {
            int16_t VBias;
            WAVEGENCLK_SPEED_t wavegenClkSpeed;
            uint32_t wavegenFraction;
            uint16_t initialPhase;
            uint16_t amplitude;
        }DCSineWave;
        
        /* ACNode_Potentiostatic */
        struct
        {
            uint16_t dummyVar;
        }ACPot;
        
        /* ACNode_Galvanostatic */
        struct
        {
            uint16_t dummyVar;
        }ACGalv;
        
        /* ACNode_Hybrid */
        struct
        {
            uint16_t dummyVar;
        }ACHybrid;
    };
}ExperimentNode_t;

#pragma(pop)

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif