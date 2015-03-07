#include "gmock\gmock.h"
#include <vector>
#include <memory>

#include "StarPlanner.h"
#include "Node.h"
#include "Graph.h"

using namespace std;
using namespace ::testing;

/*
class StarPlannerTest : public ::testing::Test{

};
*/

class NodeMock : public Node{
public:
	MOCK_CONST_METHOD1(IsEqual, bool(const Node& node));
};
class GraphMock : public Graph{
public:
	MOCK_CONST_METHOD1(GetNeighbors, std::vector<shared_ptr<Node>>(const Node& node));
};

TEST(StarPlanner, FindPlanPassSameNodeReturnsZeroNodes)
{
	GraphMock graph;
	StarPlanner planner(graph);
	auto node = make_shared<NodeMock>();
	ON_CALL(*node, IsEqual(Ref(*node))).WillByDefault(Return(true));

	vector<shared_ptr<Node>> plan = planner.FindPlan(node, node);

	ASSERT_EQ(plan.size(), 0);
}
TEST(StarPlanner, FindPlanPassAdjacentNodesReturnsOneNode){
	GraphMock graph;
	StarPlanner planner(graph);
	auto startNode = make_shared<NodeMock>();
	auto adjacentNode = make_shared<NodeMock>();
	vector<shared_ptr<Node>> adjacentNodes{ adjacentNode };
	ON_CALL(*startNode, IsEqual(Ref(*adjacentNode))).WillByDefault(Return(false));
	ON_CALL(graph, GetNeighbors(Ref(*startNode))).WillByDefault(Return(adjacentNodes));

	vector<shared_ptr<Node>> plan = planner.FindPlan(startNode, adjacentNode);

	ASSERT_EQ(plan.size(), 1);
}
TEST(StarPlanner, GetAdjacentNodesValidGraphReturnsThreeAdjacentNodes){
	GraphMock graph;
	StarPlanner planner(graph);
	// Test so that adjacent nodes are returned correctly
}