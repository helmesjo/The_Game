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

	node1->FCost = 5;
	node2->FCost = 10;
	openList.Add(node1);
	openList.Add(node2);

	auto bestNode = openList.PopBest();
	ASSERT_TRUE(bestNode == node1);
}