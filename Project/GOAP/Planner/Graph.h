#pragma once

#include <vector>
#include <memory>

struct Node;

struct Graph{
	virtual ~Graph(){}
	virtual std::vector<std::shared_ptr<Node>> GetNeighbors(const Node& node) const = 0;
};