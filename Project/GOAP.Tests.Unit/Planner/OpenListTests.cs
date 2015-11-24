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

			plannerList.AddOrUpdate(node);

			bool hasNext = plannerList.HasNext();
			Assert.IsTrue(hasNext);
		}

		[Test]
		public void PopNext_AddTwoNodesAndSetValueBeforeAdd_ReturnsNodeWithLowestFCost()
		{
			var plannerList = CreateOpenList();
			var node1 = PlannerUtil.CreateFakeNode();
			var node2 = PlannerUtil.CreateFakeNode();
			node1.EstimatedTotalCost.Returns(10f);
			node2.EstimatedTotalCost.Returns(5f);
			plannerList.AddOrUpdate(node1);
			plannerList.AddOrUpdate(node2);

			var nextNode = plannerList.PopNext();

			Assert.AreSame(nextNode, node2);
		}

		[Test]
		public void PopNext_AddTwoNodesAndSetValueAfterAdd_ReturnsNodeFirstAdded()
		{
			var plannerList = CreateOpenList();
			var node1 = PlannerUtil.CreateFakeNode();
			var node2 = PlannerUtil.CreateFakeNode();
			plannerList.AddOrUpdate(node1);
			plannerList.AddOrUpdate(node2);
			node1.EstimatedTotalCost.Returns(10f);
			node2.EstimatedTotalCost.Returns(5f);

			var nextNode = plannerList.PopNext();

			Assert.AreSame(nextNode, node1);
		}

		[Test]
		public void PopNext_AddTwoNodesAndSetValueAfterAddThenUpdate_ReturnsNodeWithLowestFCost()
		{
			var plannerList = CreateOpenList();
			var node1 = PlannerUtil.CreateFakeNode();
			var node2 = PlannerUtil.CreateFakeNode();
			plannerList.AddOrUpdate(node1);
			plannerList.AddOrUpdate(node2);
			node1.EstimatedTotalCost.Returns(10f);
			node2.EstimatedTotalCost.Returns(5f);
			plannerList.AddOrUpdate(node1);
			plannerList.AddOrUpdate(node2);

			var nextNode = plannerList.PopNext();

			Assert.AreSame(nextNode, node2);
		}

		[Test]
		public void HasNode_AddNode_ReturnsTrue()
		{
			var plannerList = CreateOpenList();
			var node = PlannerUtil.CreateFakeNode();
			plannerList.AddOrUpdate(node);

			bool hasNext = plannerList.HasNode(node);

			Assert.IsTrue(hasNext);
		}

		[Test]
		public void HasNext_AddAndPop_ReturnsFalse()
		{
			var plannerList = CreateOpenList();
			var node = PlannerUtil.CreateFakeNode();
			plannerList.AddOrUpdate(node);
			plannerList.PopNext();

			bool hasNext = plannerList.HasNode(node);

			Assert.IsFalse(hasNext);
		}

		[Test]
		public void Clear_AddNode_RemovesNode()
		{
			var plannerList = CreateOpenList();
			var node = PlannerUtil.CreateFakeNode();
			plannerList.AddOrUpdate(node);

			plannerList.Clear();

			bool hasNode = plannerList.HasNode(node);
			Assert.IsFalse(hasNode);
		}

		private static IPlannerList CreateOpenList()
		{
			return new OpenList();
		}
	}
}
