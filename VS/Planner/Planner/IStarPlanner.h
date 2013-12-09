#pragma once

class PlannerNodeBase;
class IPlannerGraph;
class PlannerPlan;

class IStarPlanner{
public:
	virtual ~IStarPlanner(){}

	virtual PlannerPlan FindPlan(PlannerNodeBase* startNode, PlannerNodeBase* endNode, IPlannerGraph* graph) = 0;
};