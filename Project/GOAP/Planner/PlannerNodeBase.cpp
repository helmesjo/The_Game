#include "PlannerNodeBase.h"

PlannerNodeBase::PlannerNodeBase():
	Parent(nullptr),
	CostSoFar(0.0f),
	Heuristic(0.0f),
	EstimatedTotalCost(0.0f),
	State(NodeState::UNVISITED),
	tempIsNeighbor(false),
	tempIsCurrent(false)
{}
void PlannerNodeBase::Reset()
{
	Parent = nullptr;
	CostSoFar = 0.0f;
	Heuristic = 0.0f;
	EstimatedTotalCost = 0.0f;
	State = NodeState::UNVISITED;
	tempIsNeighbor = false;
	tempIsCurrent = false;
}
