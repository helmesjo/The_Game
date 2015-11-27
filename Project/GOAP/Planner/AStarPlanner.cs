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
			var plan = new INode[] { };
            visitedNodes.Clear();
			ResetNode(ref startNode);
			startNode.EstimatedTotalCost = float.MaxValue;

			visitedNodes.AddOrUpdate(startNode);
			while (visitedNodes.HasNext())
			{
				var currentNode = visitedNodes.PopNext();
				currentNode.IsClosed = true;

				if (graph.IsDone(currentNode, endNode))
				{
					plan = graph.BuildPlan(currentNode);
					break;
				}

				var neighbors = graph.GetNeighbors(currentNode);

				foreach (var neighbor in neighbors)
				{
					if (neighbor.IsClosed)
						continue;

					float costSoFar = currentNode.CostSoFar + currentNode.Cost;

					bool hasNotBeenVisited = !visitedNodes.HasNode(neighbor);
					bool isBetterPlan = costSoFar < neighbor.CostSoFar;
                    if (hasNotBeenVisited || isBetterPlan)
					{
						neighbor.Parent = currentNode;
						neighbor.CostSoFar = costSoFar;
						neighbor.EstimatedTotalCost = costSoFar + graph.CalculateEstimatedCost(neighbor, endNode);
						visitedNodes.AddOrUpdate(neighbor);
					}
				}
			}

			return plan;
		}

		private static void ResetNode(ref INode startNode)
		{
			startNode.Parent = null;
			startNode.CostSoFar = 0f;
			startNode.EstimatedTotalCost = 0f;
			startNode.IsClosed = false;
        }
	}
}