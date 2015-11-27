namespace GOAP.Planner
{
	public interface IGraph
	{
		bool HasNode(INode node);
		INode[] GetNeighbors(INode node);
		float CalculateEstimatedCost(INode currentNode, INode endNode);
		bool IsDone(INode currentNode, INode endNode);
		INode[] BuildPlan(INode endNode);
	}
}