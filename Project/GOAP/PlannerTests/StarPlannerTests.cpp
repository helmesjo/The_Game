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

class FakeObject{};
class GraphMock : public IGraph<FakeObject>{
public:
	MOCK_CONST_METHOD1(getNeighbors, std::vector<FakeObject*>(const FakeObject& node));
	MOCK_CONST_METHOD2(calculateHeuristicCost, float(const FakeObject& node1, const FakeObject& node2));
};

TEST(StarPlanner, FindPlan_PassSameNode_ReturnsEmptyPlan)
{
	GraphMock graph;
	StarPlanner<FakeObject> planner(graph);
	auto node = make_shared<Node<FakeObject>>();

	vector<shared_ptr<Node<FakeObject>>> plan = planner.findPlan(node, node);

	ASSERT_EQ(plan.size(), 0);
}
TEST(StarPlanner, FindPlan_PassTwoAdjacentNodes_ReturnsSizeTwo){
	// Arrange
	GraphMock graph;
	StarPlanner<FakeObject> planner(graph);
	auto startNode = make_shared<Node<FakeObject>>();
	auto adjacentNode = make_shared<Node<FakeObject>>();
	vector<shared_ptr<Node<FakeObject>>> adjacentNodes{ adjacentNode };
	ON_CALL(graph, getNeighbors(Ref(*startNode))).WillByDefault(Return(adjacentNodes));
	// Act
	vector<shared_ptr<Node<FakeObject>>> plan = planner.findPlan(startNode, adjacentNode);
	// Assert
	ASSERT_EQ(plan.size(), 2);
}
/*
TEST(StarPlanner, FindPlan_PassMultiplePathNodes_ReturnsCorrectPlan){
	auto startNode = make_shared<PathNode>(0, 0);
	auto node1 = make_shared<PathNode>(1, 0);
	auto node2 = make_shared<PathNode>(2, 0);
	auto node3 = make_shared<PathNode>(3, 0);
	auto node4 = make_shared<PathNode>(3, 1);
	auto node5 = make_shared<PathNode>(3, 2);
	auto endNode = make_shared<PathNode>(3, 3);
	PathGraph pathGraph({ startNode, node1, node2, node3, node4, node5, endNode });
	StarPlanner<PathNode> planner(pathGraph);

	auto nodes = planner.findPlan(startNode, endNode);

	ASSERT_EQ(nodes.size(), 7);
}
*/