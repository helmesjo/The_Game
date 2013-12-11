#pragma once

#include "PlannerPlan.h"
#include "PlannerNodeBase.h"
#include <vector>
#include <unordered_map>
#include <functional>

class PlannerGraphBase{
public:
	virtual ~PlannerGraphBase(){}

	virtual PlannerPlan						BuildPlan(std::vector<PlannerNodeBase*> nodes)					= 0;
	virtual std::vector<PlannerNodeBase*>	GetNeighbors(PlannerNodeBase* node)								= 0;
	virtual float							CalculateCost(PlannerNodeBase *from, PlannerNodeBase* to)		= 0;
	virtual float							CalculateHeuristic(PlannerNodeBase* from, PlannerNodeBase* to)	= 0;
	virtual bool							IsFinished(PlannerNodeBase* node, PlannerNodeBase* endNode)		= 0;

protected:
	PlannerNodeBase*						GetReusableNode(int id, std::function<PlannerNodeBase*()> createNode);
private:
	std::unordered_map<int, PlannerNodeBase*>	m_NodeTable;
};