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

TEST(OpenList, AddAddOneNodeReturnsSizeOne){
	OpenList openList;
	auto node = make_shared<NodeMock>();

	openList.Add(node);

	ASSERT_EQ(openList.size(), 1);
}
TEST(OpenList, AddAddThreeNodesReturnsNodeWithLowestFCost){
	// Arrange
	OpenList openList;
	auto node1 = make_shared<NodeMock>();
	auto node2 = make_shared<NodeMock>();
	auto node3 = make_shared<NodeMock>();
	node1->EstimatedTotalCost = 8;
	node2->EstimatedTotalCost = 5;
	node3->EstimatedTotalCost = 10;
	openList.Add(node1);
	openList.Add(node2);
	openList.Add(node3);
	// Act
	auto bestNode = openList.PopBest();
	// Assert
	ASSERT_TRUE(bestNode == node2);
}
TEST(OpenList, AddAddSameNodeTwiceReturnsSizeOne){
	OpenList openList;
	auto node = make_shared<NodeMock>();

	openList.Add(node);
	openList.Add(node);

	ASSERT_EQ(openList.size(), 1);
}
TEST(OpenList, AddReaddNodeWithBetterFScoreReturnsNodeFirst){
	// Arrange
	OpenList openList;
	auto node1 = make_shared<NodeMock>();
	auto node2 = make_shared<NodeMock>();
	node1->EstimatedTotalCost = 8;
	node2->EstimatedTotalCost = 5;
	openList.Add(node1);
	openList.Add(node2);
	// Act
	node1->EstimatedTotalCost = 3;
	openList.Add(node1);
	// Assert
	ASSERT_TRUE(openList.PopBest() == node1);
}
TEST(OpenList, PopBestEmptyListThrowsException){
	OpenList openList;

	ASSERT_EQ(openList.size(), 0);
	EXPECT_THROW(openList.PopBest(), std::out_of_range);
}
TEST(OpenList, ClearAddNodesReturnsSizeZero){
	// Arrange
	OpenList openList;
	auto node1 = make_shared<NodeMock>();
	auto node2 = make_shared<NodeMock>();
	openList.Add(node1);
	openList.Add(node2);
	// Act
	openList.clear();
	// Assert
	ASSERT_EQ(openList.size(), 0);
}