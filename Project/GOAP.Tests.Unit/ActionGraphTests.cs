using System;
using System.Collections.Generic;
using System.Linq;

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
			var node = GOAPUtil.CreateFakeNode();
			var graph = CreateActionGraph(node);

			bool hasNode = graph.HasNode(node);

			Assert.IsTrue(hasNode);
		}

		[Test]
		public void HasNode_EmptyGraph_ReturnsFalse()
		{
			var node = GOAPUtil.CreateFakeNode();
			var graph = CreateActionGraph();

			bool hasNode = graph.HasNode(node);

			Assert.IsFalse(hasNode);
		}

		[Test]
		public void BuildPlan_NestThreeNodes_ReturnsNodes()
		{
			var node1 = GOAPUtil.CreateFakeNode();
			var node2 = GOAPUtil.CreateFakeNode();
			node2.Parent.Returns(node1);
			var node3 = GOAPUtil.CreateFakeNode();
			node3.Parent.Returns(node2);
			var graph = CreateActionGraph(node1, node2, node3);
			var expectedPlan = new IAction[] { node1.Action, node2.Action, node3.Action };

			var plan = graph.BuildPlan(node3);

			Assert.AreEqual(expectedPlan, plan);
		}

		[Test]
		public void GetNeighbors_OneActionSatisfyingPrecondition_ReturnsAction()
		{
			var node1 = GOAPUtil.CreateFakeNode();
			var node2 = GOAPUtil.CreateFakeNode();
			node2.SatisfiesPrecondition(node1.State).Returns(true);
			var graph = CreateActionGraph(node1, node2);

			var neighbors = graph.GetNeighbors(node1);

			Assert.AreSame(node2, neighbors.ElementAt(0));
		}

		[Test]
		public void GetNeighbors_NoActionSatisfyingPrecondition_ReturnsNoAction()
		{
			var node1 = GOAPUtil.CreateFakeNode();
			var node2 = GOAPUtil.CreateFakeNode();
			var graph = CreateActionGraph(node1, node2);

			var neighbors = graph.GetNeighbors(node1);

			Assert.IsEmpty(neighbors);
		}

		[Test]
		public void CalculateEstimatedCost_TwoNodeStatesWithOneDifferentProperty_ReturnsCost()
		{
			string propertyKey = "IsTrue";
			var stateProperty1 = GOAPUtil.CreateFakeStateProperty(propertyKey, false);
			var stateProperty2 = GOAPUtil.CreateFakeStateProperty(propertyKey, true);
            var state1 = GOAPUtil.CreateFakeWorldState(stateProperty1);
			var state2 = GOAPUtil.CreateFakeWorldState(stateProperty2);
			var node1 = GOAPUtil.CreateFakeNode(state1);
			var node2 = GOAPUtil.CreateFakeNode(state2);
			var actionGraph = CreateActionGraph(node1, node2);
			const float expectedCost = 1f;

			var estimatedCost = actionGraph.CalculateEstimatedCost(node1, node2);

			Assert.AreEqual(expectedCost, estimatedCost);
		}

		[Test]
		public void IsDone_TwoEqualStates_ReturnsTrue()
		{
			string propertyKey = "PropKey";
			var stateProperty1 = GOAPUtil.CreateFakeStateProperty(propertyKey, false);
			var state1 = GOAPUtil.CreateFakeWorldState(stateProperty1);
			var state2 = GOAPUtil.CreateFakeWorldState(stateProperty1);
			var node1 = GOAPUtil.CreateFakeNode(state1);
			var node2 = GOAPUtil.CreateFakeNode(state2);
			var graph = CreateActionGraph(node1, node2);

			bool isDone = graph.IsDone(node1, node2);

			Assert.IsTrue(isDone);
		}

		[Test]
		public void IsDone_TwoNoneEqualStates_ReturnsFalse()
		{
			string propertyKey = "PropKey";
			var stateProperty1 = GOAPUtil.CreateFakeStateProperty(propertyKey, false);
			var stateProperty2 = GOAPUtil.CreateFakeStateProperty(propertyKey, true);
			var state1 = GOAPUtil.CreateFakeWorldState(stateProperty1);
			var state2 = GOAPUtil.CreateFakeWorldState(stateProperty2);
			var node1 = GOAPUtil.CreateFakeNode(state1);
			var node2 = GOAPUtil.CreateFakeNode(state2);
			var graph = CreateActionGraph(node1, node2);

			bool isDone = graph.IsDone(node1, node2);

			Assert.IsFalse(isDone);
		}

		private static IGraph<IAction> CreateActionGraph(params IGOAPNode[] nodes)
		{
			return new ActionGraph(nodes);
		}
	}
}
