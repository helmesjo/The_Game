#include "gmock\gmock.h"
#include <vector>
#include <memory>

#include "StarPlanner.h"
#include "Node.h"

using namespace std;

/*
class StarPlannerTest : public ::testing::Test{

};
*/

class NodeMock : public Node{
public:
};

TEST(StarPlanner, FindPlanPassingSameNodeReturnsEmptyPlan)
{
	StarPlanner planner;
	NodeMock node;

	vector<unique_ptr<Node>> plan = planner.FindPlan(node, node);

	ASSERT_EQ(plan.size(), 0);
}