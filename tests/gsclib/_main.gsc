#include sr\tests\_main;

// Main tests
testLib()
{
	suit("GSCLIB Tests");

	sr\tests\gsclib\_tests_linq::test();
	sr\tests\gsclib\_tests_utility::test();
	sr\tests\gsclib\_tests_data::test();
	sr\tests\gsclib\_tests_net::test();
}

// Test predicate
testPredicate(item)
{
	return isDefined(item) && item != 5;
}

// Test predicate vector
testPredicateVector(item)
{
	return isDefined(item) && item != (0, 0, 0);
}

// Test predicate string
testPredicateString(item)
{
	return isDefined(item) && item != "Iswenzz";
}

// test predicate array
testPredicateArray(item)
{
	return isDefined(item) && isDefined(item.size) && item.size != 10;
}

// test predicate struct.name
testPredicateStructString(item)
{
	return isDefined(item) && isDefined(item.string) && item.string != "M1014";
}

// test predicate struct.int
testPredicateStructInt(item)
{
	return isDefined(item) && isDefined(item.int) && item.int != 8;
}

// Test delegate struct.string
testDelegateStructString(item)
{
	if (isDefined(item) && isDefined(item.string))
		return item.string;
	else
		return "";
}

// Test delegate struct.int
testDelegateStructInt(item)
{
	if (isDefined(item) && isDefined(item.int))
		return item.int;
	else
		return 0;
}

// Test predicate player ent
testPredicateEnt(player)
{
	return isDefined(player) && isDefined(player.name) && player.name != "Iswenzz";
}
