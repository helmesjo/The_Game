#pragma once

class PlannerNodeBase{
public:
	enum class NodeState{ UNVISITED = 0, OPEN, CLOSED };

	PlannerNodeBase();

	void				Reset();

	bool tempIsCurrent;
	bool tempIsNeighbor;

	PlannerNodeBase*	Parent;
	float				CostSoFar;
	float				Heuristic;
	float				EstimatedTotalCost;
	NodeState			State;

	bool operator < (const PlannerNodeBase& node){
		return this->EstimatedTotalCost < node.EstimatedTotalCost;
	}
};