#include sr\libs\gscunit\_main;
#include sr\libs\gsclib\__test__\_suite;

main()
{
	suite("GSCLIB Sys");

	// sys/system
	it(::test_GetSysTime, "GetSysTime");
	it(::test_System, "System");
	it(::test_Version, "Version");
}

test_System()
{
	EXPECT_EQ(System("cd"), 0);
	EXPECT_NE(System("error"), 0);
}

test_GetSysTime()
{
	EXPECT_GT(GetSysTime(), 0);
}

test_Version()
{
	EXPECT_TRUE(CoD4X_Version());
	EXPECT_TRUE(CGSC_Version());
	EXPECT_TRUE(GSCLIB_Version());
}
