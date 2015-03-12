#pragma once

#include "Graph.h"
#include <vector>
#include <memory>

class PathNode;

class PathGraph{
public:
	virtual ~PathGraph(){}

	PathGraph(std::vector<std::shared_ptr<PathNode>> nodes);
	PathGraph(const std::initializer_list<std::shared_ptr<PathNode>> nodes);

	virtual std::vector<PathNode*> getNeighbors(const PathNode& node) const;
	virtual float calculateHeuristicCost(const PathNode& fromNode, const PathNode& toNode) const;

private:
	std::vector<std::shared_ptr<PathNode>> m_Nodes;
};