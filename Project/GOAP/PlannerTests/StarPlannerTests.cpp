#include "gmock\gmock.h"
#include <vector>
#include <memory>

#include "StarPlanner.h"
#include "Node.h"
#include "Graph.h"

using namespace std;

/*
class StarPlannerTest : public ::testing::Test{

};
*/

class NodeMock : public Node{};
class GraphMock : public Graph{
public:
	MOCK_CONST_METHOD1(GetNeighbors, std::vector<weak_ptr<Node>>(const Node& node));
};

TEST(StarPlanner, FindPlanPassSameNodeReturnsZeroNodes)
{
	GraphMock graph;
	StarPlanner planner(graph);
	NodeMock node;

	vector<weak_ptr<Node>> plan = planner.FindPlan(node, node);

	ASSERT_EQ(plan.size(), 0);
}
TEST(StarPlanner, FindPlanPassAdjacentNodesReturnsOneNode){
	GraphMock graph;
	StarPlanner planner(graph);
	NodeMock startNode;
	NodeMock adjacentNode;
	ON_CALL(graph, GetNeighbors(adjacentNode));

	vector<weak_ptr<Node>> plan = planner.FindPlan(startNode, adjacentNode);

	ASSERT_EQ(plan.size(), 1);
}
