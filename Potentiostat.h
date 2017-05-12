#ifndef POTENTIOSTAT_H
#define	POTENTIOSTAT_H

#include "global_typedefs.h"
#include "cal.h"
#include "DAC_ADC_Buffer_types.h"
#include "Experiment.h"
#include "ComPacket.h"

class Potentiostat {
public:
    Potentiostat();
    Potentiostat(const Potentiostat& orig);
    virtual ~Potentiostat();
    
	void init(DACBuffer_t * DACBuf1, DACBuffer_t * DACBuf2, ADCBuffer_t * ADCBuf1, ADCBuffer_t * ADCBuf2);
#define CHANNEL_NAME_LENGTH 32	
	char channelName[CHANNEL_NAME_LENGTH];
	uint8_t channelNum;
	InstrStatus_t status;
	opmode_t opmode;
	cal_t cal;

	void runExperiment(uint64_t tNow);
	bool isCurrentNodeFinished(uint64_t tNow);
	InstrStatus_t initNextNode(uint64_t tNow);
	void updateDummyStates(uint64_t tNow);
	Notifications_t checkOvervoltage();
	Notifications_t checkOvercurrent();
	Notifications_t checkUndercurrent();
	void * getExperimentNodesPointer();

private:
	/* General settings */
	Experiment_t experiment;
    currentRange_t currentRange;
    currentRangeMode_t currentRangeMode;
	int16_t DCVctrl;
	int16_t overcurrentCount;
	int16_t undercurrentCount;
	int16_t EceOvervoltageCount;
	int16_t EweOvervoltageCount;
	int16_t RefOvervoltageCount;
    
    /* DC data buffers */
    ADCdc_datastruct_t ADCdc_data_now;
    uint64_t timestamp;
	uint64_t last_tSample;
    ADCBuffer_t * ADCdcActiveBuf;
    ADCBuffer_t * ADCdcInactiveBuf;
    DACBuffer_t * DACdcActiveBuf;
    DACBuffer_t * DACdcInactiveBuf;

    
	int16_t updateDummyVCtrl(uint64_t tNow);
	int16_t currentFormula(int16_t DAC);
	currentRange_t currentRangeFormula(int16_t DAC);
};

#endif	/* POTENTIOSTAT_H */

