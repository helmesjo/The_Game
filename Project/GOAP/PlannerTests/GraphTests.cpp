#include "gmock\gmock.h"
#include <vector>
#include <memory>

#include "Graph.h"
#include "Node.h"

using namespace std;
using namespace ::testing;
using namespace Planner;

class FakeObject{};
class FakeGraph{
public:
	//MOCK_CONST_METHOD1(getNeighbors, std::vector<const FakeObject*>(const FakeObject& node));
	MOCK_CONST_METHOD2(calculateHeuristicCost, float(const FakeObject& node1, const FakeObject& node2));
	//MOCK_CONST_METHOD2(isPlanDone, bool(const FakeObject& obj1, const FakeObject& obj2));
	//MOCK_CONST_METHOD1(buildPlan, std::vector<const FakeObject*>(const Node<FakeObject>& node1));
};

TEST(Graph, calculateHeuristicCost_PassValidNodes_ReturnsCorrectHeuristicCost){
	FakeObject object1;
	FakeObject object2;
	FakeGraph fakeGraph;
	auto node1 = make_shared<Node<FakeObject>>(object1);
	auto node2 = make_shared<Node<FakeObject>>(object2);
	Graph<FakeObject, FakeGraph> graph(fakeGraph);
	ON_CALL(fakeGraph, calculateHeuristicCost(Ref(node1->getObject()), Ref(node2->getObject()))).WillByDefault(Return(10.0f));

	float heuristics = graph.calculateHeuristicCost(*node1, *node2);

	ASSERT_EQ(heuristics, 10);
}

TEST(Graph, isPlanDone_PassValidNodes_ReturnsTrue){
	FakeObject object1;
	FakeGraph fakeGraph;
	Graph<FakeObject, FakeGraph> graph(fakeGraph);

	bool isPlanDone = graph.isPlanDone(object1, object1);

	ASSERT_EQ(isPlanDone, true);
}

TEST(Graph, buildPlan_PassValidNodes_ReturnsCorrectPlan){
	// Arrange
	FakeObject object1;
	FakeObject object2;
	FakeObject object3;
	FakeGraph fakeGraph;
	auto node1 = make_shared<Node<FakeObject>>(object1);
	auto node2 = make_shared<Node<FakeObject>>(object2);
	auto node3 = make_shared<Node<FakeObject>>(object3);
	node3->setParent(node2.get());
	node2->setParent(node1.get());
	Graph<FakeObject, FakeGraph> graph(fakeGraph);

	// Act
	auto plan = graph.buildPlan(*node3);

	// Assert
	ASSERT_EQ(plan.size(), 3);
	ASSERT_TRUE(plan[0] == &object1);
	ASSERT_TRUE(plan[1] == &object2);
	ASSERT_TRUE(plan[2] == &object3);
}