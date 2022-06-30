#include sr\libs\gscunit\_main;
#include sr\libs\gsclib\__test__\_suite;

main()
{
	suite("GSCLIB Sys");

	// sys/system
	it(::test_GetSysTime, "GetSysTime");
	it(::test_System, "System");
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
