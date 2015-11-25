using GOAP.Planner;

namespace GOAP
{
	public interface IAction : INode
	{
		object Precondition { get; set; }

		bool SatisfiesPrecondition(object precondition);
	}
}