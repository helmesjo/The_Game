using System.Collections.Generic;

using NSubstitute;
using GOAP.Planner;

namespace GOAP.Tests.Unit.Planner
{
	internal static class PlannerUtil
	{

		internal static IPlannerList CreatePlannerList()
		{
			var plannerList = Substitute.For<IPlannerList>();
			return plannerList;
		}

		internal static IGraph CreateGraphWithMultiplePlans(out INode startNode, out INode endNode, out INode[] bestPlan)
		{
			startNode = CreateFakeNode();
			endNode = CreateFakeNode();
			var node11 = CreateFakeNode();
			var node12 = CreateFakeNode();
			var node21 = CreateFakeNode();

			var graph = CreateFakeGraph(startNode, node11, node12, endNode);

			graph.GetNeighbors(startNode).Returns(new INode[] { node11, node12 });
			graph.GetNeighbors(node11).Returns(new INode[] { startNode, node12, node21 });
			graph.GetNeighbors(node12).Returns(new INode[] { startNode, node11, node21 });
			graph.GetNeighbors(node21).Returns(new INode[] { node11, node12, endNode });

			const float startToNode11Cost = 5f;
			const float startToNode12Cost = 11f;
			const float node11ToNode12Cost = 5f;
			const float node11ToNode21Cost = 20f;
			const float node12ToNode11Cost = 10f;
			const float node12ToNode21Cost = 10f;
			const float node21ToEndCost = 10f;
			graph.CalculateCost(startNode, node11).Returns(startToNode11Cost);
			graph.CalculateCost(startNode, node12).Returns(startToNode12Cost);
			graph.CalculateCost(node11, node12).Returns(node11ToNode12Cost);
			graph.CalculateCost(node11, node21).Returns(node11ToNode21Cost);
			graph.CalculateCost(node12, node11).Returns(node12ToNode11Cost);
			graph.CalculateCost(node12, node21).Returns(node12ToNode21Cost);
			graph.CalculateCost(node21, endNode).Returns(node21ToEndCost);
			graph.CalculateEstimatedCost(Arg.Any<INode>(), Arg.Any<INode>()).Returns(5f);

			graph.IsDone(endNode, endNode).Returns(true);

			bestPlan = new INode[] { startNode, node11, node12, node21, endNode };

			return graph;
		}

		internal static IGraph CreateFakeGraph(params INode[] nodes)
		{
			var graph = Substitute.For<IGraph>();
			graph.IsDone(Arg.Any<INode>(), Arg.Any<INode>()).Returns(false);

			graph.HasNode(Arg.Any<INode>()).Returns(callInfo => {
				var passedNode = callInfo.Arg<INode>();
                foreach (var node in nodes)
					if (node == passedNode)
						return true;
				return false;
			});

			graph.BuildPlan(Arg.Any<INode>()).Returns(callInfo => {
				var plan = new Stack<INode>();
				var node = callInfo.Arg<INode>();

				plan.Push(node);
				while (node.Parent != null)
				{
					node = node.Parent;
					plan.Push(node);
				}

				return plan.ToArray();
			});

			return graph;
		}

		internal static INode CreateFakeNode()
		{
			var node = Substitute.For<INode>();
            return node;
		}
	}
}
