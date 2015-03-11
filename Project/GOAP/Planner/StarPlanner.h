#pragma once

#include "Planner.h"
#include "OpenList.h"

template<class T>
class Graph;

template<class T>
class StarPlanner : public Planner<T>{
public:
	StarPlanner(const Graph& graph);
	virtual std::vector<std::shared_ptr<Node<T>> findPlan(const std::shared_ptr<Node<T>>& startNode, const std::shared_ptr<Node<T>>& endNode) override;

private:
	const Graph& graph;
	OpenList m_OpenList;
};

/*
template<class T>
StarPlanner<T>::StarPlanner(const Graph<T>& graph) : graph(graph){}
template<class T>
std::vector<std::shared_ptr<Node<T>>> StarPlanner<T>::findPlan(const std::shared_ptr<Node<T>>& startNode, const std::shared_ptr<Node<T>>& endNode){
	std::vector<std::shared_ptr<Node<T>> nodes;
	if (startNode == endNode)
		return nodes;

	// 1. Add startnode to openlist
	m_OpenList.add(startNode);

	// 2. Iterate until openlist empty
	std::shared_ptr<Node<T>> currentNode;
	std::vector<std::shared_ptr<Node<T>>> neighborNodes;
	while (m_OpenList.size() > 0){
		currentNode = m_OpenList.popBest();
		// 3. Get the best node (F-score) from the openlist and add it to the closed list.
		// Stop if currentNode is the endNode (plan has been found)
		if (currentNode == endNode){
			// Traverse the tree until end (start)
			std::weak_ptr<Node<T>> parentNode = currentNode;
			while (!parentNode.expired()){
				nodes.insert(nodes.begin(), parentNode.lock());
				parentNode = parentNode.lock()->getParent();
			}
			break;
		}

		// 4. Get & iterate all adjacent nodes
		neighborNodes = graph.getNeighbors(*currentNode);
		for (auto neighborNode : neighborNodes){
			Node::State nodeState = neighborNode->getState();
			// 5. If it's in the closed list, ignore it
			if (nodeState == Node::State::Closed)
				continue;

			// 6. Calculate new G- & H-costs
			float costSoFar = currentNode->getCostSoFar() + neighborNode->getCost();
			float heuristicCost = graph.calculateHeuristicCost(*neighborNode, *endNode);
			float estimatedTotalCost = costSoFar + heuristicCost;

			// 7.1. If it's not in the openlist, set currentNode as parent and calculate the G- & H-costs and add it.
			if (nodeState == State::None){
				neighborNode->setParent(currentNode);
				neighborNode->setCostSoFar(costSoFar);
				neighborNode->setHeuristicCost(heuristicCost);
				m_OpenList.add(neighborNode);
			}
			// 7.2. If it's already in the openlist, check if new G- & H-costs are better. If so update and re-add it.
			else if (nodeState == Node::State::Open && neighborNode->getEstimatedTotalCost() > estimatedTotalCost){
				neighborNode->setParent(currentNode);
				neighborNode->setCostSoFar(costSoFar);
				neighborNode->setHeuristicCost(heuristicCost);
				m_OpenList.add(neighborNode);
			}
		}
	}
	/*
	return nodes;
}
*/
