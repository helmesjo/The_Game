#pragma once

class PlannerNodeBase;
class PlannerGraphBase;
class PlannerPlan;

class IStarPlanner{
public:
	virtual ~IStarPlanner(){}

	virtual PlannerPlan FindPlan(PlannerNodeBase* startNode, PlannerNodeBase* endNode, PlannerGraphBase* graph) = 0;
};