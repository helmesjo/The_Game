using GOAP.Planner;

namespace GOAP
{
	public interface IGOAPNode : INode
	{
		IAction Action { get; }
		IWorldState State { get; }

		bool SatisfiesPrecondition(object precondition);
	}
}