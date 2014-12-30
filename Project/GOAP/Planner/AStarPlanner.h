#pragma once

#include "IStarPlanner.h"
#include "AStarOpenList.h"

class AStarPlanner : public IStarPlanner{
public:
	virtual PlannerPlan FindPlan( PlannerNodeBase* startNode, PlannerNodeBase* endNode, PlannerGraphBase* graph );

private:
	AStarOpenList	m_OpenList;
};