using System;
using System.Collections.Generic;

using NUnit.Framework;
using NSubstitute;

using GOAP.Planner;

namespace GOAP.Tests.Unit.GOAP
{
	[TestFixture]
	class ActionGraphTests
	{

		[Test]
		public void HasNode_AddNode_ReturnsTrue()
		{
			var action = GOAPUtil.CreateFakeAction();
			var graph = CreateActionGraph(action);

			bool hasNode = graph.HasNode(action);

			Assert.IsTrue(hasNode);
		}

		[Test]
		public void HasNode_EmptyGraph_ReturnsFalse()
		{
			var action = GOAPUtil.CreateFakeAction();
			var graph = CreateActionGraph();

			bool hasNode = graph.HasNode(action);

			Assert.IsFalse(hasNode);
		}

		[Test]
		public void BuildPlan_NestThreeNodes_ReturnsNodes()
		{
			var action1 = GOAPUtil.CreateFakeAction();
			var action2 = GOAPUtil.CreateFakeAction();
			action2.Parent.Returns(action1);
			var action3 = GOAPUtil.CreateFakeAction();
			action3.Parent.Returns(action2);
			var graph = CreateActionGraph(action1, action2, action3);
			var expectedPlan = new INode[] { action1, action2, action3 };

			var plan = graph.BuildPlan(action3);

			Assert.AreEqual(expectedPlan, plan);
		}

		[Test]
		public void GetNeighbors_OneActionSatisfyingPrecondition_ReturnsAction()
		{
			var action1 = GOAPUtil.CreateFakeAction();
			var action2 = GOAPUtil.CreateFakeAction();
			action2.SatisfiesPrecondition(action1.Precondition).Returns(true);
			var graph = CreateActionGraph(action1, action2);

			var neighbors = graph.GetNeighbors(action1);

			Assert.AreSame(action2, neighbors[0]);
		}

		[Test]
		public void GetNeighbors_NoActionSatisfyingPrecondition_ReturnsNoAction()
		{
			var action1 = GOAPUtil.CreateFakeAction();
			var action2 = GOAPUtil.CreateFakeAction();
			var graph = CreateActionGraph(action1, action2);

			var neighbors = graph.GetNeighbors(action1);

			Assert.IsEmpty(neighbors);
		}

		[Test]
		public void CalculateEstimatedCost_TwoValidActions_ReturnsCost()
		{
			var action1 = GOAPUtil.CreateFakeAction();
			var action2 = GOAPUtil.CreateFakeAction();
			var actionGraph = CreateActionGraph(action1, action2);
			const float expectedCost = 1f;

			var estimatedCost = actionGraph.CalculateEstimatedCost(action1, action2);

			Assert.AreEqual(expectedCost, estimatedCost);
		}

		private static IGraph CreateActionGraph(params IAction[] actions)
		{
			return new ActionGraph(actions);
		}
	}
}
