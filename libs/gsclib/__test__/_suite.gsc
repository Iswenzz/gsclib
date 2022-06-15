#include sr\libs\gscunit\_main;

gsclib()
{
	env();
	suite("GSCLIB");

	sr\libs\gsclib\__test__\_test_data::main();
	sr\libs\gsclib\__test__\_test_linq::main();
	sr\libs\gsclib\__test__\_test_net::main();
	sr\libs\gsclib\__test__\_test_sys::main();
	sr\libs\gsclib\__test__\_test_utils::main();
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

predicate(item, index)
{
	return item != 5;
}

predicateVector(item, index)
{
	return item != (0, 0, 0);
}

predicateString(item, index)
{
	return item != "Iswenzz";
}

predicateArray(item, index)
{
	return item.size != 10;
}

predicateEnt(player, index)
{
	return player.name != "Iswenzz";
}

predicateStructString(item, index)
{
	return item.string != "M1014";
}

predicateStructInt(item, index)
{
	return item.int != 8;
}

delegateStructString(item, index)
{
	return item.string;
}

delegateStructInt(item, index)
{
	return item.int;
}

delegateForeachIncrement(item, index)
{
	item.value++;
}

delagateAggregateInt(previous, current, index)
{
	return previous + current;
}

env()
{
	// Float array
	level.tests.floats = [];
	for (i = 0; i < 10; i++)
		level.tests.floats[i] = i * 1.05;

	// Int array
	level.tests.ints = [];
	for (i = 0; i < 10; i++)
		level.tests.ints[i] = i;

	// String array
	level.tests.strings = strTok("Ellin;Alexa;Celiza;Iswenzz;10", ";");

	// Vector array
	level.tests.vectors = [];
	for (i = 0; i < 10; i++)
		level.tests.vectors[i] = (level.tests.floats[i], level.tests.floats[i], level.tests.floats[i]);

	// Struct array
	level.tests.structs = [];
	level.tests.structs[0] = SpawnStruct();
	level.tests.structs[0].string = "AK47";
	level.tests.structs[0].int = 30;
	level.tests.structs[0].vector = (100, 200, 300);
	level.tests.structs[0].array = level.tests.ints;
	level.tests.structs[0].float = 1.5;
	level.tests.structs[1] = SpawnStruct();
	level.tests.structs[1].string = "Desert Eagle";
	level.tests.structs[1].int = 12;
	level.tests.structs[1].vector = (400, 500, 600);
	level.tests.structs[1].array = level.tests.floats;
	level.tests.structs[1].float = 2.5;
	level.tests.structs[2] = SpawnStruct();
	level.tests.structs[2].string = "M1014";
	level.tests.structs[2].int = 8;
	level.tests.structs[2].vector = (700, 800, 900);
	level.tests.structs[2].array = level.tests.strings;
	level.tests.structs[2].float = 3.5;

	// 2D array
	level.tests.arrays = [];
	level.tests.arrays[level.tests.arrays.size] = level.tests.floats;
	level.tests.arrays[level.tests.arrays.size] = level.tests.ints;
	level.tests.arrays[level.tests.arrays.size] = level.tests.vectors;
	level.tests.arrays[level.tests.arrays.size] = level.tests.structs;

	// Ent array
	level.tests.ents = getEntArray("player", "classname");
}
