#include "Experiment.h"
#include "Arduino.h"

Experiment_t::Experiment_t() {}
Experiment_t::Experiment_t(const Experiment_t& orig) {}
Experiment_t::~Experiment_t() {}

InstrStatus_t Experiment_t::initNode(int16_t nextNode, uint64_t tNow)
{
	nodeIndex = nextNode;
	nodes[nodeIndex].t_start = tNow;
	switch (nodes[nodeIndex].nodeType)
	{
	case DCNODE_OCP:
		return OCP;
		break;
	case DCNODE_SWEEP:
	case DCNODE_POINT:
	case DCNODE_NORMALPULSE:
	case DCNODE_DIFFPULSE:
	case DCNODE_SQRWAVE:
	case DCNODE_SINEWAVE:
		return DC_NODE_ACTIVE;
		break;
	case ACNODE_POTENTIOSTATIC:
	case ACNODE_GALVANOSTATIC:
	case ACNODE_HYBRID:
		return AC_NODE_ACTIVE;
	case END_EXPERIMENT_NODE:
		return EXPERIMENT_COMPLETED;
	default:
		return CHANNEL_ERROR;
		break;
	}
}

uint16_t Experiment_t::SeekNextNode()
{
	ExperimentNode_t * pNode = &nodes[nodeIndex];
	if (pNode->isTail)
	{
		if (++(pNode->numPlays) >= pNode->MaxPlays)
		{
			return nodeIndex + 1;
		}
		else
		{
			return pNode->branchHeadIndex;
		}
	}
	else
	{
		return nodeIndex + 1;
	}
}