using GOAP.Planner;

namespace GOAP
{
	public interface IPlanner
	{
		INode[] FindPlan(INode start, INode end);
	}
}