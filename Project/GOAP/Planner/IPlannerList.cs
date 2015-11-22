using System.Collections;

namespace GOAP.Planner
{
	public interface IPlannerList
	{
		void AddOrRefresh(INode node);
	}
}