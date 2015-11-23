using System.Collections;

namespace GOAP.Planner
{
	public interface IPlannerList
	{
		void Add(INode node);
		bool HasNext();
		INode PopNext();
		bool HasNode(INode node);
	}
}