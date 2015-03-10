#include "gmock\gmock.h"
#include <vector>
#include <memory>

#include "StarPlanner.h"
#include "Node.h"
#include "Graph.h"

#include "PathGraph.h"
#include "PathNode.h"

using namespace std;
using namespace ::testing;

/*
class StarPlannerTest : public ::testing::Test{

};
*/

class NodeMock : public Node{};
class GraphMock : public Graph{
public:
	MOCK_CONST_METHOD1(getNeighbors, std::vector<shared_ptr<Node>>(const Node& node));
};

TEST(StarPlanner, FindPlan_PassSameNode_ReturnsEmptyPlan)
{
	GraphMock graph;
	StarPlanner planner(graph);
	auto node = make_shared<NodeMock>();

	vector<shared_ptr<Node>> plan = planner.findPlan(node, node);

	ASSERT_EQ(plan.size(), 0);
}
TEST(StarPlanner, FindPlan_PassTwoAdjacentNodes_ReturnsSizeOne){
	// Arrange
	GraphMock graph;
	StarPlanner planner(graph);
	auto startNode = make_shared<NodeMock>();
	auto adjacentNode = make_shared<NodeMock>();
	vector<shared_ptr<Node>> adjacentNodes{ adjacentNode };
	ON_CALL(graph, getNeighbors(Ref(*startNode))).WillByDefault(Return(adjacentNodes));
	// Act
	vector<shared_ptr<Node>> plan = planner.findPlan(startNode, adjacentNode);
	// Assert
	ASSERT_EQ(plan.size(), 1);
}
TEST(StarPlanner, FindPlan_PassMultiplePathNodes_ReturnsCorrectPlan){
	auto startNode = make_shared<PathNode>(0, 0);
	auto node1 = make_shared<PathNode>(1, 0);
	auto node2 = make_shared<PathNode>(2, 0);
	auto node3 = make_shared<PathNode>(3, 0);
	auto node4 = make_shared<PathNode>(3, 1);
	auto node5 = make_shared<PathNode>(3, 2);
	auto endNode = make_shared<PathNode>(3, 3);
	PathGraph pathGraph({ startNode, node1, node2, node3, node4, node5, endNode });
	StarPlanner planner(pathGraph);

	auto nodes = planner.findPlan(startNode, endNode);

	ASSERT_EQ(nodes.size(), 7);
}