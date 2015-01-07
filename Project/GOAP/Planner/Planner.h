#pragma once

#include <vector>
#include <memory>

class Node;

class Planner{
public:
	virtual ~Planner(){}
	virtual std::vector<std::weak_ptr<Node>> FindPlan(const Node& startNode, const Node& endNode) = 0;
};