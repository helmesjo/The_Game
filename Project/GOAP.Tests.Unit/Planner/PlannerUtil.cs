using System.Collections.Generic;

using NSubstitute;
using GOAP.Planner;

namespace GOAP.Tests.Unit.Planner
{
	static class PlannerUtil
	{
		public static IGraph CreateFakeGraph(params INode[] nodes)
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

		public static INode CreateFakeNode()
		{
			return Substitute.For<INode>();
		}
	}
}
