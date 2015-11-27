using GOAP.Planner;

namespace GOAP
{
	public interface IAction : INode
	{
		IWorldState[] Precondition { get; set; }

		bool SatisfiesPrecondition(object precondition);
	}
}