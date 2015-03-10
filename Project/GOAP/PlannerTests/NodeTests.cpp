#include "gmock\gmock.h"
#include <vector>
#include <memory>

#include "Node.h"

using namespace std;

class NodeMock : public Node{};

TEST(Node, SetCostSoFarValidValueReturnsSameValue){
	auto node = make_shared<NodeMock>();

	node->setCostSoFar(10);

	ASSERT_EQ(node->getCostSoFar(), 10);
}
TEST(Node, SetHeuristicCostValidValueReturnsSameValue){
	auto node = make_shared<NodeMock>();

	node->setHeuristicCost(5);

	ASSERT_EQ(node->getHeuristicCost(), 5);
}
TEST(Node, SetCostsValidValuesReturnsCorrectEstimatedTotalValue){
	auto node = make_shared<NodeMock>();

	node->setCostSoFar(10);
	node->setHeuristicCost(5);

	ASSERT_EQ(node->getEstimatedTotalCost(), 15);
}
TEST(Node, SetStateAllStatesReturnsState){
	auto node = make_shared<NodeMock>();

	node->setState(Node::State::Open);
	ASSERT_EQ(node->getState(), Node::State::Open);
	node->setState(Node::State::Closed);
	ASSERT_EQ(node->getState(), Node::State::Closed);
}