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

class NodeMock : public Node{};
class GraphMock : public Graph{
public:
	MOCK_CONST_METHOD1(GetNeighbors, std::vector<shared_ptr<Node>>(const Node& node));
};

TEST(StarPlanner, FindPlanPassSameNodeReturnsZeroNodes)
{
	GraphMock graph;
	StarPlanner planner(graph);
	auto node = make_shared<NodeMock>();

	vector<shared_ptr<Node>> plan = planner.FindPlan(node, node);

	ASSERT_EQ(plan.size(), 0);
}
TEST(StarPlanner, FindPlanPassAdjacentNodesReturnsOneNode){
	// Arrange
	GraphMock graph;
	StarPlanner planner(graph);
	auto startNode = make_shared<NodeMock>();
	auto adjacentNode = make_shared<NodeMock>();
	vector<shared_ptr<Node>> adjacentNodes{ adjacentNode };
	ON_CALL(graph, GetNeighbors(Ref(*startNode))).WillByDefault(Return(adjacentNodes));
	// Act
	vector<shared_ptr<Node>> plan = planner.FindPlan(startNode, adjacentNode);
	// Assert
	ASSERT_EQ(plan.size(), 1);
}