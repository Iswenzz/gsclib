#include sr\tests\_main;

test()
{
	suit("GSCLIB Tests");

	sr\tests\gsclib\_tests_linq::test();
	sr\tests\gsclib\_tests_utils::test();
	sr\tests\gsclib\_tests_data::test();
	sr\tests\gsclib\_tests_net::test();
}

testPredicate(item)
{
	return isDefined(item) && item != 5;
}

testPredicateVector(item)
{
	return isDefined(item) && item != (0, 0, 0);
}

testPredicateString(item)
{
	return isDefined(item) && item != "Iswenzz";
}

testPredicateArray(item)
{
	return isDefined(item) && isDefined(item.size) && item.size != 10;
}

testPredicateStructString(item)
{
	return isDefined(item) && isDefined(item.string) && item.string != "M1014";
}

testPredicateStructInt(item)
{
	return isDefined(item) && isDefined(item.int) && item.int != 8;
}

testDelegateStructString(item)
{
	if (isDefined(item) && isDefined(item.string))
		return item.string;
	else
		return "";
}

testDelegateStructInt(item)
{
	if (isDefined(item) && isDefined(item.int))
		return item.int;
	else
		return 0;
}

testPredicateEnt(player)
{
	return isDefined(player) && isDefined(player.name) && player.name != "Iswenzz";
}
