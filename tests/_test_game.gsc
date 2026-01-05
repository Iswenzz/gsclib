#include sr\libs\gscunit\_main;
#include sr\libs\gsclib\__test__\_suite;

main()
{
	suite("GSCLIB Game");

	// Game/Player
	it(::test_GetIP, "GetIP");
	it(::test_GetForwardMove, "GetForwardMove");
	it(::test_GetRightMove, "GetRightMove");
	it(::test_PmFlags, "PmFlags");
	it(::test_PmTime, "PmTime");
	it(::test_PmType, "PmType");
	it(::test_WeaponFlags, "WeaponFlags");
}

test_GetIP()
{
	EXPECT_EQ(level.gscunit.bots[0] GetIP(), "bot");
}

test_GetForwardMove()
{
	EXPECT_EQ(level.gscunit.bots[0] GetForwardMove(), 0);
}

test_GetRightMove()
{
	EXPECT_EQ(level.gscunit.bots[0] GetRightMove(), 0);
}

test_PmFlags()
{
	EXPECT_EQ(level.gscunit.bots[0] PmFlags(), 0);
}

test_PmTime()
{
	EXPECT_EQ(level.gscunit.bots[0] PmTime(), 0);
}

test_PmType()
{
	EXPECT_EQ(level.gscunit.bots[0] PmType(), 0);
}

test_WeaponFlags()
{
	EXPECT_EQ(level.gscunit.bots[0] WeaponFlags(), 0);
}
