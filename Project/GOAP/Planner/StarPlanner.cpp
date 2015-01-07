#include "StarPlanner.h"
#include "Node.h"
#include "Graph.h"

using namespace std;

StarPlanner::StarPlanner(const Graph& graph):
graph(graph){

}
vector<weak_ptr<Node>> StarPlanner::FindPlan(const Node& startNode, const Node& endNode){
	vector<weak_ptr<Node>> nodes;

	if (startNode == endNode)
		return nodes;

	// Get adjacent nodes
	vector<weak_ptr<Node>> neighborNodes = graph.GetNeighbors(startNode);

	for each (weak_ptr<Node> node in neighborNodes)
		nodes.push_back(node);

	return nodes;
}