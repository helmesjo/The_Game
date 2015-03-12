#pragma once

#include "Planner.h"
#include "OpenList.h"
#include "Node.h"
#include "Graph.h"

template<class T, class Y>
class StarPlanner{
public:
	StarPlanner(Y& graph);
	std::vector<const T*> findPlan(const T& startNode, const T& endNode);

private:
	Graph<T, Y> graph;
	OpenList<T> m_OpenList;
};


template<class T, class Y>
StarPlanner<T, Y>::StarPlanner(Y& graph) 
	: graph(Graph<T, Y>(graph))
{}
template<class T, class Y>
std::vector<const T*> StarPlanner<T, Y>::findPlan(const T& startNode, const T& endNode){
	std::vector<const T*> nodes;
	
	if (&startNode == &endNode)
		return nodes;

	auto start = graph.getNode(startNode);

	// 1. Add startnode to openlist
	m_OpenList.add(start);

	// 2. Iterate until openlist empty
	while (m_OpenList.size() > 0){
		auto currentNode = m_OpenList.popBest();
		// 3. Get the best node (F-score) from the openlist and add it to the closed list.
		// Stop if currentNode is the endNode (plan has been found)
		if (&currentNode.getObject() == &endNode){
			// Traverse the tree until end (start)
			const Node<T>* parentNode = &currentNode;
			while (parentNode != nullptr){
				nodes.insert(nodes.begin(), &parentNode->getObject());
				parentNode = parentNode->getParent();
			}
			break;
		}

		// 4. Get & iterate all adjacent nodes
		auto neighborNodes = graph.getNeighbors(currentNode.getObject());
		for (auto neighborNode : neighborNodes){
			State nodeState = neighborNode->getState();
			// 5. If it's in the closed list, ignore it
			if (nodeState == State::Closed)
				continue;

			// 6. Calculate new G- & H-costs
			float costSoFar = currentNode.getCostSoFar() + neighborNode->getCost();
			float heuristicCost = graph.calculateHeuristicCost(*neighborNode, endNode);
			float estimatedTotalCost = costSoFar + heuristicCost;

			// 7.1. If it's not in the openlist, set currentNode as parent and calculate the G- & H-costs and add it.
			if (nodeState == State::None){
				neighborNode->setParent(currentNode);
				neighborNode->setCostSoFar(costSoFar);
				neighborNode->setHeuristicCost(heuristicCost);
				m_OpenList.add(*neighborNode);
			}
			// 7.2. If it's already in the openlist, check if new G- & H-costs are better. If so update and re-add it.
			else if (nodeState == State::Open && neighborNode->getEstimatedTotalCost() > estimatedTotalCost){
				neighborNode->setParent(currentNode);
				neighborNode->setCostSoFar(costSoFar);
				neighborNode->setHeuristicCost(heuristicCost);
				m_OpenList.add(*neighborNode);
			}
		}
	}
	
	
	return nodes;
}