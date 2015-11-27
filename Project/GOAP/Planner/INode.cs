using C5;

namespace GOAP.Planner
{
	public interface INode
	{
		float Cost { get; }
		float CostSoFar { get; set; }
		float EstimatedTotalCost { get; set; }
		bool IsClosed { get; set; }
		INode Parent { get; set; }
		IPriorityQueueHandle<INode> QueueHandle { get; set; }
	}
}