/* 
 * File:   ExperimentNode.h
 * Author: Matt
 *
 * Created on April 5, 2017, 12:22 AM
 */

#ifndef EXPERIMENT_H
#define	EXPERIMENT_H

#include "ExperimentNode.h"
#include "DAC_ADC_Buffer_types.h"

#define MAX_NODES 128

class Experiment_t {
public:
    Experiment_t();
    Experiment_t(const Experiment_t& orig);
    virtual ~Experiment_t();
    void HandleExperiment();
    bool isNodeFinished(int16_t Vctrl, int16_t Ewe, int16_t _I, currentRange_t currentRange, uint64_t tNow);
    void initNextNode();
    void refreshBuffer(DACBuffer_t * DACbuf);
    void toggleDACBuffers();
    NodeType_t currentNodeType;
    uint16_t nodeIndex;
    ExperimentNode_t nodes[MAX_NODES];
    
//private:
	void checkNodeProgress(uint64_t tNow, int16_t DCVCtrl, int16_t ewe, int16_t _I, uint8_t currentRange);
    uint16_t SeekNextNode();
    void initNode(int16_t nextNode);
    void fillDACBuf(DACBuffer_t * dacBuf, uint16_t nodeIndex);
    
//private:
    
    //void calculateSignalGenParams(ACNode_t * ACNode);
    bool calculateACNodePassFail(int16_t * EWErawdata, int16_t * Irawdata);
};

#endif	/* EXPERIMENT_H */

