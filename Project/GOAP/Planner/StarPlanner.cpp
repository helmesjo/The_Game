#include "StarPlanner.h"
#include "Node.h"
#include "Graph.h"

using namespace std;

StarPlanner::StarPlanner(const Graph& graph):
graph(graph){

}
vector<shared_ptr<Node>> StarPlanner::FindPlan(const shared_ptr<Node>& startNode, const shared_ptr<Node>& endNode){
	vector<shared_ptr<Node>> nodes;

	if (startNode == endNode)
		return nodes;

	m_OpenList.Add(startNode);

	shared_ptr<Node> currentNode;
	vector<shared_ptr<Node>> neighborNodes;
	while (m_OpenList.size() > 0){
		currentNode = m_OpenList.PopBest();
		// Get adjacent nodes
		neighborNodes = graph.GetNeighbors(*startNode);

		for (auto node : neighborNodes)
			nodes.push_back(node);
	}

	return nodes;
}