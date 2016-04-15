using System.Collections.Generic;

namespace GOAP.Planner
{
	public interface IGraph<T>
	{
		bool HasNode(INode node);
		ICollection<INode> GetNeighbors(INode node);
		float CalculateEstimatedCost(INode currentNode, INode endNode);
		bool IsDone(INode currentNode, INode endNode);
		ICollection<T> BuildPlan(INode endNode);
	}
}