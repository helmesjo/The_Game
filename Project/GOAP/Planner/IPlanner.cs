using GOAP.Planner;

namespace GOAP
{
	public interface IPlanner<T>
	{
		T[] FindPlan(INode start, INode end);
	}
}