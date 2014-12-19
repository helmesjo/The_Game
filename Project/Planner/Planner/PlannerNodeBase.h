#pragma once

class PlannerNodeBase{
public:
	enum class NodeState{ UNVISITED = 0, OPEN, CLOSED };

	PlannerNodeBase();

	void				Reset();

	bool tempIsCurrent;
	bool tempIsNeighbor;

#pragma region Data
	PlannerNodeBase*	Parent;
	float				CostSoFar;
	float				Heuristic;
	float				EstimatedTotalCost;
	NodeState			State;
#pragma endregion

	bool operator < (const PlannerNodeBase& node){
		return this->EstimatedTotalCost < node.EstimatedTotalCost;
	}
};