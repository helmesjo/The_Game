#pragma once

#include "PlannerPlan.h"
#include "PlannerNodeBase.h"
#include <vector>
#include <unordered_map>
#include <functional>

class PlannerGraphBase{
public:
	virtual ~PlannerGraphBase(){}

#pragma region virtual
	virtual PlannerPlan						BuildPlan(std::vector<PlannerNodeBase*> nodes)					= 0;
	virtual std::vector<PlannerNodeBase*>	GetNeighbors(PlannerNodeBase* node)								= 0;
	virtual float							CalculateCost(PlannerNodeBase *from, PlannerNodeBase* to)		= 0;
	virtual float							CalculateHeuristic(PlannerNodeBase* from, PlannerNodeBase* to)	= 0;
	virtual bool							IsFinished(PlannerNodeBase* node, PlannerNodeBase* endNode)		= 0;
	virtual void							DebugPrint() = 0;
#pragma endregion

	PlannerNodeBase*						GetReusableNode(const int id, const std::function<PlannerNodeBase*()>& createNode);
	std::vector<PlannerNodeBase*>			GetNodes();
	void									Reset();
private:
	std::unordered_map<size_t, PlannerNodeBase*>	m_NodeTable;
};