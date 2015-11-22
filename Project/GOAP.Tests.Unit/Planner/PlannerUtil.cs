using NSubstitute;
using GOAP.Planner;

namespace GOAP.Tests.Unit.Planner
{
	static class PlannerUtil
	{
		public static IGraph CreateFakeGraph(params INode[] nodes)
		{
			var graph = Substitute.For<IGraph>();

			return graph;
		}

		public static INode CreateFakeNode()
		{
			return Substitute.For<INode>();
		}
	}
}
