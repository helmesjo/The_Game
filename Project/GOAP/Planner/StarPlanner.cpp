#include "StarPlanner.h"
#include "Node.h"
#include "Graph.h"

using namespace std;

StarPlanner::StarPlanner(const Graph& graph):
graph(graph){

}
vector<shared_ptr<Node>> StarPlanner::findPlan(const shared_ptr<Node>& startNode, const shared_ptr<Node>& endNode){
	vector<shared_ptr<Node>> nodes;

	if (startNode == endNode)
		return nodes;

	// 1. Add startnode to openlist
	m_OpenList.add(startNode);

	// 2. Iterate until openlist empty
	shared_ptr<Node> currentNode;
	vector<shared_ptr<Node>> neighborNodes;
	while (m_OpenList.size() > 0){
		// 3. Get the best node (F-score) from the openlist and add it to the closed list.
		// Stop if currentNode is the endNode (plan has been found)
		currentNode = m_OpenList.popBest();
		currentNode->setState(Node::State::Closed);
		// 4. Get & iterate all adjacent nodes
		neighborNodes = graph.getNeighbors(*startNode);
		for (auto neighborNode : neighborNodes){
			Node::State nodeState = neighborNode->getState();
			// 5. If it's in the closed list, ignore it
			if (nodeState == Node::State::Closed)
				continue;

			// 6. Calculate new G- & H-costs
			float costSoFar = currentNode->getCostSoFar() + neighborNode->getCost();
			float heuristicCost = graph.calculateHeuristicCost(neighborNode, *endNode);

			// 7.1. If it's not in the openlist, set currentNode as parent and calculate the G- & H-costs and add it.
			if (nodeState == Node::State::None){

			}
			// 7.2. If it's already in the openlist, check if new G- & H-costs are better. If so update and re-add it.

			nodes.push_back(neighborNode);
		}
	}

	return nodes;
}