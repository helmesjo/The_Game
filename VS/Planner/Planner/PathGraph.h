#pragma once

#include "PlannerGraphBase.h"
#include "PathNode.h"

#include <vector>


class PathGraph : public PlannerGraphBase{
public:
	PathGraph();

#pragma region IPlannerGraph
	virtual PlannerPlan							BuildPlan(std::vector<PlannerNodeBase*> nodes);
	virtual std::vector<PlannerNodeBase*>		GetNeighbors(PlannerNodeBase* node);
	virtual float								CalculateCost(PlannerNodeBase *from, PlannerNodeBase* to);
	virtual float								CalculateHeuristic( PlannerNodeBase* from, PlannerNodeBase* to );
	virtual bool								IsFinished(PlannerNodeBase* node, PlannerNodeBase* endNode);
#pragma endregion IPlannerGraph

private:
};