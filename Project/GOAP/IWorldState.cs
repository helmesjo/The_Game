using System.Collections.Generic;

namespace GOAP
{
	public interface IWorldState
	{
		IWorldStateProperty[] Properties { get; }

		bool IsPropertySame(IWorldStateProperty property);
		bool doesSatisfy(IWorldState state);
	}
}