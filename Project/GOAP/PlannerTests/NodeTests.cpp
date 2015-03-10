#include "gmock\gmock.h"
#include <vector>
#include <memory>

#include "Node.h"

using namespace std;

class NodeMock : public Node{};

TEST(Node, SetCostSoFar_ValidValue_ReturnsSameValue){
	auto node = make_shared<NodeMock>();

	node->setCostSoFar(10);

	ASSERT_EQ(node->getCostSoFar(), 10);
}
TEST(Node, SetHeuristicCost_ValidValue_ReturnsSameValue){
	auto node = make_shared<NodeMock>();

	node->setHeuristicCost(5);

	ASSERT_EQ(node->getHeuristicCost(), 5);
}
TEST(Node, SetAllCosts_ValidValues_ReturnsCorrectEstimatedTotalValue){
	auto node = make_shared<NodeMock>();

	node->setCostSoFar(10);
	node->setHeuristicCost(5);

	ASSERT_EQ(node->getEstimatedTotalCost(), 15);
}
TEST(Node, SetState_AllStates_ReturnsCorrect){
	auto node = make_shared<NodeMock>();

	node->setState(Node::State::None);
	ASSERT_EQ(node->getState(), Node::State::None);
	node->setState(Node::State::Open);
	ASSERT_EQ(node->getState(), Node::State::Open);
	node->setState(Node::State::Closed);
	ASSERT_EQ(node->getState(), Node::State::Closed);
}