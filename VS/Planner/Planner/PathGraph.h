#pragma once

#include "PlannerGraphBase.h"
#include "PathNode.h"

#include <vector>

class PathGraph : public PlannerGraphBase{
public:
	static const int	WIDTH = 20;
	static const int	HEIGHT = 20;

	PathGraph();

	virtual void DebugPrint();

#pragma region PlannerGraphBase
	virtual PlannerPlan							BuildPlan(std::vector<PlannerNodeBase*> nodes);
	virtual std::vector<PlannerNodeBase*>		GetNeighbors(PlannerNodeBase* node);
	virtual float								CalculateCost(PlannerNodeBase *from, PlannerNodeBase* to);
	virtual float								CalculateHeuristic( PlannerNodeBase* from, PlannerNodeBase* to );
	virtual bool								IsFinished(PlannerNodeBase* node, PlannerNodeBase* endNode);
#pragma endregion PlannerGraphBase

private:
	char		m_Grid[WIDTH][HEIGHT];
	char		m_DefaultGrid[WIDTH][HEIGHT];
};