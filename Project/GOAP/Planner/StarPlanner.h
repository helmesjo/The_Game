#pragma once

#include "Planner.h"

class Graph;

class StarPlanner : public Planner{
public:
	StarPlanner(const Graph& graph);
	virtual std::vector<std::weak_ptr<Node>> FindPlan(const Node& startNode, const Node& endNode);

private:
	const Graph& graph;
};