#include "StarPlanner.h"
#include "Node.h"
#include "Graph.h"

using namespace std;

StarPlanner::StarPlanner(const Graph& graph):
graph(graph){

}
vector<shared_ptr<Node>> StarPlanner::FindPlan(const shared_ptr<Node>& startNode, const shared_ptr<Node>& endNode){
	vector<shared_ptr<Node>> nodes;

	if (startNode->IsEqual(*endNode))
		return nodes;

	// Get adjacent nodes
	vector<shared_ptr<Node>> neighborNodes = graph.GetNeighbors(*startNode);

	for (auto node : neighborNodes)
		nodes.push_back(node);

	return nodes;
}