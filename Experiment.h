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

#define MAX_NODES 32

class Experiment_t {
public:
    Experiment_t();
    Experiment_t(const Experiment_t& orig);
    virtual ~Experiment_t();
    NodeType_t currentNodeType;
    uint16_t nodeIndex;
    ExperimentNode_t nodes[MAX_NODES];
    uint16_t SeekNextNode();
	InstrStatus_t initNode(int16_t nextNode, uint64_t tNow);
};

#endif	/* EXPERIMENT_H */

