#pragma once

#include "Planner.h"

struct Graph;

class StarPlanner : public Planner{
public:
	StarPlanner(const Graph& graph);
	virtual std::vector<std::shared_ptr<Node>> FindPlan(const std::shared_ptr<Node>& startNode, const std::shared_ptr<Node>& endNode);

private:
	const Graph& graph;
};