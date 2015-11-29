namespace GOAP
{
	public interface IWorldStateProperty
	{
		string Key { get; }
		bool Value { get; }

		bool IsSame(IWorldStateProperty prop);
	}
}