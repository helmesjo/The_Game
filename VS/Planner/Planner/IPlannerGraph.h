#pragma once

#include <vector>

class PlannerNodeBase;
class PlannerPlan;

class IPlannerGraph{
public:
	virtual ~IPlannerGraph(){}

	virtual PlannerPlan						BuildPlan(std::vector<PlannerNodeBase*> nodes) = 0;
	virtual std::vector<PlannerNodeBase*>	GetNeighbors(PlannerNodeBase* node) = 0;
	virtual float							CalculateCost(PlannerNodeBase *from, PlannerNodeBase* to) = 0;
	virtual float							CalculateHeuristic(PlannerNodeBase* from, PlannerNodeBase* to) = 0;
	virtual bool							IsFinished(PlannerNodeBase* node) = 0;
};