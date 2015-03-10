#pragma once

#include <vector>
#include <memory>

struct Node;

struct Graph{
	virtual ~Graph(){}
	virtual std::vector<std::shared_ptr<Node>> getNeighbors(const Node& node) const = 0;
	virtual float calculateHeuristicCost(const Node& fromNode, const Node& toNode) const = 0;
};