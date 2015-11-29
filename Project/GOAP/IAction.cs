using GOAP.Planner;

namespace GOAP
{
	public interface IGOAPNode : INode
	{
		IWorldState State { get; }

		bool SatisfiesPrecondition(object precondition);
	}
}