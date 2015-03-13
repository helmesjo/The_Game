#include "gmock\gmock.h"
#include <vector>
#include <memory>

#include "OpenList.h"
#include "Node.h"

using namespace std;
using namespace ::testing;
using namespace Planner;

//class NodeMock : public Node{};

class FakeObject{};

TEST(OpenList, Add_AddOneNode_ReturnsSizeOne){
	FakeObject object;
	OpenList<FakeObject> openList;
	auto node = make_shared<Node<FakeObject>>(object);

	openList.add(*node);

	ASSERT_EQ(openList.size(), 1);
}
TEST(OpenList, Add_AddOneNode_NodeChangesStateToOpen){
	FakeObject object;
	OpenList<FakeObject> openList;
	auto node = make_shared<Node<FakeObject>>(object);

	openList.add(*node);

	ASSERT_EQ(node->getState(), State::Open);

	auto& bestNode = openList.popBest();

	ASSERT_EQ(bestNode.getState(), State::Closed);
}
TEST(OpenList, Add_AddThreeNodes_ReturnsNodeWithLowestFCost){
	// Arrange
	FakeObject object1;
	FakeObject object2;
	FakeObject object3;
	OpenList<FakeObject> openList;
	auto node1 = make_shared<Node<FakeObject>>(object1);
	auto node2 = make_shared<Node<FakeObject>>(object2);
	auto node3 = make_shared<Node<FakeObject>>(object3);
	node1->setCostSoFar(8);
	node2->setCostSoFar(5);
	node3->setCostSoFar(10);
	openList.add(*node1);
	openList.add(*node2);
	openList.add(*node3);
	// Act
	auto& bestNode = openList.popBest();
	// Assert
	ASSERT_TRUE(&bestNode == node2.get());
}
TEST(OpenList, Add_AddSameNodeTwice_ReturnsSizeOne){
	FakeObject object;
	OpenList<FakeObject> openList;
	auto node = make_shared<Node<FakeObject>>(object);

	openList.add(*node);
	openList.add(*node);

	ASSERT_EQ(openList.size(), 1);
}
TEST(OpenList, Add_ReaddNodeWithBetterFScore_ReturnsNodeWithBestF){
	// Arrange
	FakeObject object1;
	FakeObject object2;
	OpenList<FakeObject> openList;
	auto node1 = make_shared<Node<FakeObject>>(object1);
	auto node2 = make_shared<Node<FakeObject>>(object2);
	node1->setCostSoFar(8);
	node2->setCostSoFar(5);
	openList.add(*node1);
	openList.add(*node2);
	// Act
	node1->setCostSoFar(3);
	openList.add(*node1);
	// Assert
	ASSERT_TRUE(&openList.popBest() == node1.get());
}
TEST(OpenList, PopBest_EmptyList_ThrowsException){
	OpenList<FakeObject> openList;

	ASSERT_EQ(openList.size(), 0);
	EXPECT_THROW(openList.popBest(), std::out_of_range);
}
TEST(OpenList, Clear_AddNodesAndClear_ReturnsSizeZero){
	// Arrange
	FakeObject object1;
	FakeObject object2;
	OpenList<FakeObject> openList;
	auto node1 = make_shared<Node<FakeObject>>(object1);
	auto node2 = make_shared<Node<FakeObject>>(object2);
	openList.add(*node1);
	openList.add(*node2);
	// Act
	openList.clear();
	// Assert
	ASSERT_EQ(openList.size(), 0);
}