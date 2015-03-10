#include "gmock\gmock.h"
#include <vector>
#include <memory>

#include "Node.h"

using namespace std;

class NodeMock : public Node{};

TEST(Node, SetAllCosts_ValidValues_ReturnsCorrectEstimatedTotalValue){
	auto node = make_shared<NodeMock>();

	node->setCostSoFar(10);
	node->setHeuristicCost(5);

	ASSERT_EQ(node->getEstimatedTotalCost(), 15);
}