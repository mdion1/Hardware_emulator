#include "Experiment.h"

Experiment_t::Experiment_t() {
}

Experiment_t::Experiment_t(const Experiment_t& orig) {
}

Experiment_t::~Experiment_t() {
}

void Experiment_t::checkNodeProgress(uint64_t tNow, int16_t DCVCtrl, int16_t ewe, int16_t _I, uint8_t currentRange)
{
	ExperimentNode_t * pNode = &nodes[nodeIndex];
	bool retVal = false;
	switch (pNode->nodeType)
	{
		case DCNODE_OCP:
		{
			if (tNow - pNode->DCocp.tStart >= pNode->DCocp.t_interval)
				retVal = true;
		}
		break;
		case DCNODE_POINT:
		case DCNODE_SWEEP:
		{
			if ((DCVCtrl >= pNode->DCSweep.VEnd && pNode->DCSweep.dVdt > 0) ||
				(DCVCtrl <= pNode->DCSweep.VEnd && pNode->DCSweep.dVdt < 0))
				retVal = true;
		}
		break;
		case DCNODE_NORMALPULSE:
		{
			//TODO
		}
		break;
		case DCNODE_DIFFPULSE:
		{
			//TODO
		}
		break;
		case DCNODE_SQRWAVE:
		{
			//TODO
		}
		break;
		case DCNODE_SINEWAVE:
			//TODO
		case ACNODE_POTENTIOSTATIC:
			//TODO
		case ACNODE_GALVANOSTATIC:
			//TODO
		case ACNODE_HYBRID:
			//TODO
		default:
			break;
	}
}

void Experiment_t::initNode(int16_t nextNode)
{

}