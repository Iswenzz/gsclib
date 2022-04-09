#include libs\gscunit\_main;

gsclib()
{
	suite("GSCLIB");

	libs\gsclib\__test__\_test_data::main();
	libs\gsclib\__test__\_test_linq::main();
	libs\gsclib\__test__\_test_net::main();
	libs\gsclib\__test__\_test_utils::main();
}

hasFTP()
{
	return level.tests.ftp;
}

hasSFTP()
{
	return level.tests.sftp;
}

hasMySQL()
{
	return level.tests.mysql;
}

noop()
{
	return true;
}

predicate(item)
{
	return isDefined(item) && item != 5;
}

predicateVector(item)
{
	return isDefined(item) && item != (0, 0, 0);
}

predicateString(item)
{
	return isDefined(item) && item != "Iswenzz";
}

predicateArray(item)
{
	return isDefined(item) && isDefined(item.size) && item.size != 10;
}

predicateEnt(player)
{
	return isDefined(player) && isDefined(player.name) && player.name != "Iswenzz";
}

predicateStructString(item)
{
	return isDefined(item) && isDefined(item.string) && item.string != "M1014";
}

predicateStructInt(item)
{
	return isDefined(item) && isDefined(item.int) && item.int != 8;
}

delegateStructString(item)
{
	if (isDefined(item) && isDefined(item.string))
		return item.string;
	return "";
}

delegateStructInt(item)
{
	if (isDefined(item) && isDefined(item.int))
		return item.int;
	return 0;
}

delegateForeachIncrement(item)
{
	if (isDefined(item) && isDefined(item.value))
		item.value++;
}
