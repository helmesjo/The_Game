namespace GOAP.Planner
{
	public interface IGraph<T>
	{
		bool HasNode(INode node);
		INode[] GetNeighbors(INode node);
		float CalculateEstimatedCost(INode currentNode, INode endNode);
		bool IsDone(INode currentNode, INode endNode);
		T[] BuildPlan(INode endNode);
	}
}