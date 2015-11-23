namespace GOAP.Planner
{
	public interface INode
	{
		float CostSoFar { get; set; }
		float EstimatedTotalCost { get; set; }
		bool IsClosed { get; set; }
		INode Parent { get; set; }
	}
}