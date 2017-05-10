#ifndef POTENTIOSTAT_H
#define	POTENTIOSTAT_H

#include "global_typedefs.h"
#include "cal.h"
#include "DAC_ADC_Buffer_types.h"
#include "Experiment.h"

class Potentiostat {
public:
    Potentiostat();
    Potentiostat(const Potentiostat& orig);
    virtual ~Potentiostat();
    
    /* General settings */
#define CHANNEL_NAME_LENGTH 32
    Experiment_t experiment;
    char channelName[CHANNEL_NAME_LENGTH];
    uint8_t channelNum;
    status_t status;
    opmode_t opmode;
    currentRange_t currentRange;
    currentRangeMode_t currentRangeMode;
    cal_t cal;
    void init(DACBuffer_t * DACBuf1, DACBuffer_t * DACBuf2, ADCBuffer_t * ADCBuf1, ADCBuffer_t * ADCBuf2);
    
    /* DC data buffers */
    ADCdc_datastruct_t ADCdc_data_now;
    uint64_t timestamp;
	uint32_t last_tSample;
    ADCBuffer_t * ADCdcActiveBuf;
    ADCBuffer_t * ADCdcInactiveBuf;
    DACBuffer_t * DACdcActiveBuf;
    DACBuffer_t * DACdcInactiveBuf;
    
    void toggleADCbuffers();
    void toggleDACBuffers();
    void incrementADCBufIndex();
    void getDynamicAverageADCdc(ADCdc_datastruct_t * resultBuf, ADCBuffer_t * ADCBuf);
	void runExperiment();
    bool isCurrentNodeFinished(uint64_t tNow);
    void initNextNode();
	void updateDummyVCtrl(uint32_t tNow);
	void updateDummyStates();
	
	int16_t DCVctrl;
    int16_t overcurrentCount;
    int16_t undercurrentCount;
    int16_t EceOvervoltageCount;
    int16_t EweOvervoltageCount;
    int16_t RefOvervoltageCount;
    void turnOffChannel();
    channelWarnings_t checkOvervoltage();
    channelWarnings_t checkOvercurrent();
    channelWarnings_t checkUndercurrent();
    channelWarnings_t setCurrentRange(int range);
    //void initDCsamplingNode(DCNodeParameters_t * DCnodeParams);
    void stopDCsampling();
    
    /* AC settings */
    SignalGenParams_t signalGenParams;
    ADCacParams_t ADCacParams;
    uint16_t EweACbuf[1024];
    uint16_t IACbuf[1024];
    //bool isEISenabled;
    //float frequency;
    //uint32_t frequencyClkDiv;
    //uint32_t frequencyMod;
    uint32_t phase;
    //uint16_t amplitudeInt;
    //uint16_t amplitudeTargetInt;
    //float amplitudeTargetFloat;
    ACgain_t WEgain0;
    ACgain_t WEgain1;
    ACgain_t WEgain2;
    int16_t WEgainTotal;
    ACgain_t Igain0;
    ACgain_t Igain1;
    ACgain_t Igain2;
    int16_t IgainTotal;
    freq_range_t freq_range;
    //uint32_t ADCHS_clockDiv;
    //uint32_t ADCHS_clockMod;
    //float ADCHS_sig_freq;
    //uint32_t ADCHS_numSamples;
    void setSignalGenParams(SignalGenParams_t * incomingParams);
    void ADCacSamplingParams(ADCacParams_t * incomingParams);
    void StartADCacSampling();
    void StopADCacSampling();
    
    //void ACSignalSetup(int16_t DCBias, float ACamplitude, float sig_frequency, float sample_frequency, uint32_t num_samples);
            
    void ADC_DC_manualConv();
    void ADC_DC_readBuf(int16_t *resultBuf);
    void DAC_DC_manualSetCtrlV(int16_t setpoint);
    void DAC_DC_manualSetCtrlV(float setpoint);
    int16_t DAC_DC_adjustWEbias();
    void DAC_DC_manualSetWEbias(int16_t setpoint);
    int16_t DAC_DC_adjustIbias();
    void DAC_DC_manualSetIbias(int16_t setpoint);
};

#endif	/* POTENTIOSTAT_H */

