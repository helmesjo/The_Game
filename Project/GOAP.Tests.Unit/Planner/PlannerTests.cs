using System;

using NUnit.Framework;
using NSubstitute;
using GOAP.Planner;

namespace GOAP.Tests.Unit.Planner
{
	class PlannerTests
	{

		[Test]
		public void FindPlan_ValidStartAndEndNode_PlanContainsBothNodes()
		{
			var startNode = PlannerUtil.CreateFakeNode();
			var endNode = PlannerUtil.CreateFakeNode();
			var graph = PlannerUtil.CreateFakeGraph(startNode, endNode);
			graph.GetNeighbors(startNode).Returns(new INode[] { endNode });
			graph.IsDone(endNode, endNode).Returns(true);
			var planner = CreatePlanner(graph);

			var plan = planner.FindPlan(startNode, endNode);

			Assert.AreSame(startNode, plan[0]);
			Assert.AreSame(endNode, plan[plan.Length - 1]);
		}

		[Test]
		public void FindPlan_StartSameAsEnd_ReturnsPlanWithOnlyStartNode()
		{
			var startNode = PlannerUtil.CreateFakeNode();
			var graph = PlannerUtil.CreateFakeGraph(startNode);
			graph.IsDone(startNode, startNode).Returns(true);
			var planner = CreatePlanner(graph);

			var plan = planner.FindPlan(startNode, startNode);

			Assert.IsTrue(plan.Length == 1);
			Assert.AreSame(startNode, plan[0]);
		}

		[Test]
		public void FindPlan_GraphMissingNode_ReturnsEmptyPlan()
		{
			var startNode = PlannerUtil.CreateFakeNode();
			var endNode = PlannerUtil.CreateFakeNode();
			var graph = PlannerUtil.CreateFakeGraph(startNode);
			var planner = CreatePlanner(graph);

			var plan = planner.FindPlan(startNode, endNode);

			Assert.IsTrue(plan.Length == 0);
		}

		[Test]
		public void FindPlan_ThreeAdjacentNodes_ReturnsCompletePlan()
		{
			var startNode = PlannerUtil.CreateFakeNode();
			var middleNode = PlannerUtil.CreateFakeNode();
			var endNode = PlannerUtil.CreateFakeNode();
			var graph = PlannerUtil.CreateFakeGraph();
			graph.GetNeighbors(startNode).Returns(new INode[] { middleNode });
			graph.GetNeighbors(middleNode).Returns(new INode[] { endNode });
			graph.IsDone(endNode, endNode).Returns(true);
			var planner = CreatePlanner(graph);

			var plan = planner.FindPlan(startNode, endNode);

			int expectedPlanLength = 3;
			Assert.AreEqual(expectedPlanLength, plan.Length);
			Assert.AreSame(startNode, plan[0]);
			Assert.AreSame(middleNode, plan[1]);
			Assert.AreSame(endNode, plan[2]);
		}

		private static IPlanner CreatePlanner(IGraph graph)
		{
			return new AStarPlanner(graph);
		}
	}
}
