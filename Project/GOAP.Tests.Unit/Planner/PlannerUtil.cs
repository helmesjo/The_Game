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

		internal static IGraph<INode> CreateGraphWithMultiplePlans(out INode startNode, out INode endNode, out ICollection<INode> bestPlan)
		{
			startNode = CreateFakeNode();
			endNode = CreateFakeNode();
			var node1 = CreateFakeNode();
			var node2 = CreateFakeNode();
			var node3 = CreateFakeNode();

			var graph = CreateFakeGraph(startNode, node2, node3, endNode);
			//		1 - 3 - E
			// s  <	   /
			//		2

			graph.GetNeighbors(startNode).Returns(new INode[] { node1, node2 });
			graph.GetNeighbors(node1).Returns(new INode[] { startNode, node3 });
			graph.GetNeighbors(node2).Returns(new INode[] { startNode, node3 });
			graph.GetNeighbors(node3).Returns(new INode[] { node1, node2, endNode });

			node1.Cost.Returns(5f);
			node2.Cost.Returns(10f);
			node3.Cost.Returns(5f);
			graph.CalculateEstimatedCost(Arg.Any<INode>(), Arg.Any<INode>()).Returns(5f);

			graph.IsDone(endNode, endNode).Returns(true);

			bestPlan = new INode[] { startNode, node1, node3, endNode };

			return graph;
		}

		internal static IGraph<INode> CreateFakeGraph(params INode[] nodes)
		{
			var graph = Substitute.For<IGraph<INode>>();
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
