#pragma once
#include "Base.hpp"

namespace gsclib
{
	class Linq
	{
	public:
		static void Select();
		static void Foreach();
		static void Aggregate();

		static void All();
		static void Any();
		static void Where();
		static void Last();
		static void First();
		static void Count();

		static void Min();
		static void Max();
		static void Cast();
		static void OfType();
		static void Sort();
		static void Average();
		static void Sum();
		static void Range();
		static void Repeat();
		static void Reverse();
		static void Concat();
		static void Chunk();
		static void Contains();
		static void IndexOf();
		static void Remove();
		static void RemoveAt();

	private:
		static void StringMin(VariableValueArray array);
		static void VectorMin(VariableValueArray array);
		static void NumberMin(VariableValueArray array, int flags);

		static void StringMax(VariableValueArray array);
		static void VectorMax(VariableValueArray array);
		static void NumberMax(VariableValueArray array, int flags);

		static void StringCast(VariableValueArray array);
		static void IntCast(VariableValueArray array);
		static void FloatCast(VariableValueArray array);

		static void VectorAverage(VariableValueArray array);
		static void NumberAverage(VariableValueArray array, int flags);

		static void StringSum(VariableValueArray array);
		static void VectorSum(VariableValueArray array);
		static void NumberSum(VariableValueArray array, int flags);

		static bool CompareValues(const VariableValue& a, const VariableValue& b);
	};
}
