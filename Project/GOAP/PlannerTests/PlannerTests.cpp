#include "gtest/gtest.h"
#include <vector>

/*
class StarPlannerTest : public ::testing::Test{

};
*/

TEST(StarPlannerTest, NeverReturnsNull)
{
	std::vector<int> *plan = nullptr;

	ASSERT_FALSE(plan == nullptr);
}