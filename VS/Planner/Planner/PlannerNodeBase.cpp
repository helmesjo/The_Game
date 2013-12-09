#include "PlannerNodeBase.h"

PlannerNodeBase::PlannerNodeBase():
	Parent(nullptr),
	CostSoFar(0.0f),
	Heuristic(0.0f),
	EstimatedTotalCost(0.0f),
	State(UNVISITED)
{}