#pragma once

#include "Planner.h"

class StarPlanner : public Planner{
public:
	virtual std::vector<std::unique_ptr<Node>> FindPlan(const Node& startNode, const Node& endNode);
};