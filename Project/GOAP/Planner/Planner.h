#pragma once

#include <vector>
#include <memory>

class Node;

class Planner{
public:
	virtual std::vector<std::unique_ptr<Node>> FindPlan(const Node& startNode, const Node& endNode) = 0;
};