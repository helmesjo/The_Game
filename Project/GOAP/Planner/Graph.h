#pragma once

#include <vector>
#include <memory>

class Node;

class Graph{
public:
	virtual ~Graph(){}
	virtual std::vector<std::shared_ptr<Node>> GetNeighbors(const Node& node) const = 0;
};