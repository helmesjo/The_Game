#pragma once

#include <vector>
#include <memory>

class Node;

class Planner{
public:
	virtual ~Planner(){}
	virtual std::vector<std::shared_ptr<Node>> FindPlan(const std::shared_ptr<Node>& startNode, const std::shared_ptr<Node>& endNode) = 0;
};