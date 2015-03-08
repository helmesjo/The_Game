#include "gmock\gmock.h"
#include <vector>
#include <memory>

#include "OpenList.h"
#include "Node.h"

using namespace std;
using namespace ::testing;

class NodeMock : public Node{
public:
	MOCK_CONST_METHOD1(IsEqual, bool(const Node& node));
};

TEST(OpenList, AddAddTwoNodesReturnNodeWithLowestFCost){
	OpenList openList;
	auto node1 = make_shared<NodeMock>();
	auto node2 = make_shared<NodeMock>();
	auto node3 = make_shared<NodeMock>();

	node1->EstimatedTotalCost = 8;
	node2->EstimatedTotalCost = 5;
	node3->EstimatedTotalCost = 10;
	openList.Add(node1);
	openList.Add(node2);

	auto bestNode = openList.PopBest();
	ASSERT_TRUE(bestNode == node2);
}