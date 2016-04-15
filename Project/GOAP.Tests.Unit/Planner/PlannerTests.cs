using System.Linq;

using NUnit.Framework;
using NSubstitute;
using GOAP.Planner;
using System.Collections.Generic;

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

			Assert.AreSame(startNode, plan.ElementAt(0));
			Assert.AreSame(endNode, plan.ElementAt(plan.Count - 1));
		}

		[Test]
		public void FindPlan_StartSameAsEnd_ReturnsPlanWithOnlyStartNode()
		{
			var startNode = PlannerUtil.CreateFakeNode();
			var graph = PlannerUtil.CreateFakeGraph(startNode);
			graph.IsDone(startNode, startNode).Returns(true);
			var planner = CreatePlanner(graph);

			var plan = planner.FindPlan(startNode, startNode);

			Assert.IsTrue(plan.Count == 1);
			Assert.AreSame(startNode, plan.ElementAt(0));
		}

		[Test]
		public void FindPlan_GraphMissingNode_ReturnsEmptyPlan()
		{
			var startNode = PlannerUtil.CreateFakeNode();
			var endNode = PlannerUtil.CreateFakeNode();
			var graph = PlannerUtil.CreateFakeGraph(startNode);
			var planner = CreatePlanner(graph);

			var plan = planner.FindPlan(startNode, endNode);

			Assert.IsTrue(plan.Count == 0);
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
			Assert.AreEqual(expectedPlanLength, plan.Count);
			Assert.AreSame(startNode, plan.ElementAt(0));
			Assert.AreSame(middleNode, plan.ElementAt(1));
			Assert.AreSame(endNode, plan.ElementAt(2));
		}

		[Test]
		public void FindPlan_MultiplePossiblePlans_ReturnsBestPlan()
		{
			INode startNode = null;
			INode endNode = null;
			ICollection<INode> bestPlan = null;
			var graph = PlannerUtil.CreateGraphWithMultiplePlans(out startNode, out endNode, out bestPlan);
			var planner = CreatePlanner(graph);

			var plan = planner.FindPlan(startNode, endNode);

			Assert.AreEqual(bestPlan.Count, plan.Count);
			for (int i = 0; i < bestPlan.Count; ++i)
				Assert.AreSame(bestPlan.ElementAt(i), plan.ElementAt(i));
		}

		private static IPlanner<INode> CreatePlanner(IGraph<INode> graph)
		{
			return new AStarPlanner<INode>(graph);
		}
	}
}
