using GOAP.Planner;
using System.Collections.Generic;

namespace GOAP
{
	public interface IPlanner<T>
	{
		ICollection<T> FindPlan(INode start, INode end);
	}
}