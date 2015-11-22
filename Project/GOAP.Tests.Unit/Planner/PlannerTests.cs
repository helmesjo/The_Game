using System;

using NUnit.Framework;
using NSubstitute;
using GOAP.Planner;

namespace GOAP.Tests.Unit.Planner
{
	class PlannerTests
	{

		[Test]
		public void FindPlan_PassValidStartAndEndNode_ValidPlanContainsBothNodes()
		{
			var startNode = PlannerUtil.CreateFakeNode();
			var endNode = PlannerUtil.CreateFakeNode();
			var graph = PlannerUtil.CreateFakeGraph(startNode, endNode);
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

		private static IPlanner CreatePlanner(IGraph graph)
		{
			return new AStarPlanner(graph);
		}
	}
}
