#pragma once

#include "Graph.h"
#include <vector>
#include <memory>

class PathNode;

class PathGraph : public Graph{
public:
	PathGraph(std::vector<std::shared_ptr<PathNode>> nodes);
	PathGraph(const std::initializer_list<std::shared_ptr<PathNode>> nodes);

	virtual std::vector<std::shared_ptr<Node>> getNeighbors(const Node& node) const override;
	virtual float calculateHeuristicCost(const Node& fromNode, const Node& toNode) const override;

private:
	std::vector<std::shared_ptr<PathNode>> m_Nodes;
};