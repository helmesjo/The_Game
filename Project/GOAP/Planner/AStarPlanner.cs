using System;

namespace GOAP.Planner
{
	public class AStarPlanner : IPlanner
	{
		private IGraph graph;

		public AStarPlanner(IGraph graph)
		{
			this.graph = graph;
		}

		public INode[] FindPlan(INode start, INode end)
		{
			return new INode[] { start, end };
		}
	}
}