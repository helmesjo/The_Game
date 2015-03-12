#include "gmock\gmock.h"
#include <vector>
#include <memory>

#include "OpenList.h"
#include "Node.h"

using namespace std;
using namespace ::testing;

//class NodeMock : public Node{};

TEST(OpenList, Add_AddOneNode_ReturnsSizeOne){
	OpenList<int> openList;
	auto node = make_shared<Node<int>>();

	openList.add(node);

	ASSERT_EQ(openList.size(), 1);
}
TEST(OpenList, Add_AddOneNode_NodeChangesStateToOpen){
	OpenList<int> openList;
	auto node = make_shared<Node<int>>();

	openList.add(node);

	ASSERT_EQ(node->getState(), State::Open);

	node = openList.popBest();

	ASSERT_EQ(node->getState(), State::Closed);
}
TEST(OpenList, Add_AddThreeNodes_ReturnsNodeWithLowestFCost){
	// Arrange
	OpenList<int> openList;
	auto node1 = make_shared<Node<int>>();
	auto node2 = make_shared<Node<int>>();
	auto node3 = make_shared<Node<int>>();
	node1->setCostSoFar(8);
	node2->setCostSoFar(5);
	node3->setCostSoFar(10);
	openList.add(node1);
	openList.add(node2);
	openList.add(node3);
	// Act
	auto bestNode = openList.popBest();
	// Assert
	ASSERT_TRUE(bestNode == node2);
}
TEST(OpenList, Add_AddSameNodeTwice_ReturnsSizeOne){
	OpenList<int> openList;
	auto node = make_shared<Node<int>>();

	openList.add(node);
	openList.add(node);

	ASSERT_EQ(openList.size(), 1);
}
TEST(OpenList, Add_ReaddNodeWithBetterFScore_ReturnsNodeWithBestF){
	// Arrange
	OpenList<int> openList;
	auto node1 = make_shared<Node<int>>();
	auto node2 = make_shared<Node<int>>();
	node1->setCostSoFar(8);
	node2->setCostSoFar(5);
	openList.add(node1);
	openList.add(node2);
	// Act
	node1->setCostSoFar(3);
	openList.add(node1);
	// Assert
	ASSERT_TRUE(openList.popBest() == node1);
}
TEST(OpenList, PopBest_EmptyList_ThrowsException){
	OpenList<int> openList;

	ASSERT_EQ(openList.size(), 0);
	EXPECT_THROW(openList.popBest(), std::out_of_range);
}
TEST(OpenList, Clear_AddNodesAndClear_ReturnsSizeZero){
	// Arrange
	OpenList<int> openList;
	auto node1 = make_shared<Node<int>>();
	auto node2 = make_shared<Node<int>>();
	openList.add(node1);
	openList.add(node2);
	// Act
	openList.clear();
	// Assert
	ASSERT_EQ(openList.size(), 0);
}