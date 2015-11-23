using System.Collections.Generic;

namespace GOAP.Planner
{
	public class AStarPlanner : IPlanner
	{
		private IGraph graph;
		private IPlannerList visitedNodes = new OpenList();

		public AStarPlanner(IGraph graph)
		{
			this.graph = graph;
		}

		public INode[] FindPlan(INode startNode, INode endNode)
		{
			startNode.Parent = null;
            startNode.CostSoFar = 0f;
			startNode.EstimatedTotalCost = graph.CalculateEstimatedCost(startNode, endNode);

			visitedNodes.Add(startNode);

			while (visitedNodes.HasNext())
			{
				var currentNode = visitedNodes.PopNext();
				currentNode.IsClosed = true;

				if (graph.IsDone(currentNode, endNode))
					return graph.BuildPlan(currentNode);

				var neighbors = graph.GetNeighbors(currentNode);

				foreach(var neighbor in neighbors)
				{
					if (neighbor.IsClosed)
						continue;

					float costSoFar = currentNode.CostSoFar + graph.CalculateCost(currentNode, neighbor);

					if (!visitedNodes.HasNode(neighbor))
						visitedNodes.Add(neighbor);
					else if (costSoFar >= neighbor.CostSoFar)
						continue;

					neighbor.Parent = currentNode;
					neighbor.CostSoFar = costSoFar;
					neighbor.EstimatedTotalCost = costSoFar + graph.CalculateEstimatedCost(neighbor, endNode);

				}
			}
			
			return new INode[]{};
		}
	}
}