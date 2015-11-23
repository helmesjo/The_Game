using System;

using NUnit.Framework;
using NSubstitute;

using GOAP.Planner;

namespace GOAP.Tests.Unit.Planner
{
	[TestFixture]
	class OpenListTests
	{
		[Test]
		public void Add_PassNewNode_AddsTheNode()
		{
			var plannerList = CreateOpenList();
			var node = PlannerUtil.CreateFakeNode();

			plannerList.Add(node);
			bool hasNext = plannerList.HasNext();

			Assert.IsTrue(hasNext);
		}

		[Test]
		public void PopNext_AddTwoNodes_ReturnsNodeWithLowestFCost()
		{
			var plannerList = CreateOpenList();
			var node1 = PlannerUtil.CreateFakeNode();
			var node2 = PlannerUtil.CreateFakeNode();
			node1.EstimatedTotalCost.Returns(10f);
			node2.EstimatedTotalCost.Returns(5f);
			plannerList.Add(node1);
			plannerList.Add(node2);

			var nextNode = plannerList.PopNext();

			Assert.AreSame(nextNode, node2);
		}

		[Test]
		public void HasNode_AddNode_ReturnsTrue()
		{
			var plannerList = CreateOpenList();
			var node = PlannerUtil.CreateFakeNode();
			plannerList.Add(node);

			bool hasNext = plannerList.HasNode(node);

			Assert.IsTrue(hasNext);
		}

		[Test]
		public void HasNext_AddAndPop_ReturnsFalse()
		{
			var plannerList = CreateOpenList();
			var node = PlannerUtil.CreateFakeNode();
			plannerList.Add(node);
			plannerList.PopNext();

			bool hasNext = plannerList.HasNode(node);

			Assert.IsFalse(hasNext);
		}

		private static IPlannerList CreateOpenList()
		{
			return new OpenList();
		}
	}
}
