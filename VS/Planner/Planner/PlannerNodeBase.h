#pragma once

class PlannerNodeBase{
public:
	enum NodeState{	UNVISITED = 0, OPEN, CLOSED };

	PlannerNodeBase();

	PlannerNodeBase*	Parent;
	float				CostSoFar;
	float				Heuristic;
	float				EstimatedTotalCost;
	NodeState			State;

	bool operator < (const PlannerNodeBase& node){
		return this->EstimatedTotalCost < node.EstimatedTotalCost;
	}
};