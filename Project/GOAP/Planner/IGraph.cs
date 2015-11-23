namespace GOAP.Planner
{
	public interface IGraph
	{
		bool HasNode(INode start);
		INode[] GetNeighbors(INode startNode);
		float CalculateEstimatedCost(INode startNode, INode endNode);
		bool IsDone(INode currentNode, INode endNode);
		INode[] BuildPlan(INode currentNode);
		float CalculateCost(INode currentNode, INode neighbor);
	}
}