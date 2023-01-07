#include sr\libs\gscunit\_main;
#include sr\libs\gsclib\__test__\_suite;

main()
{
	suite("GSCLIB Sys");

	// sys/system
	it(::test_GetSysTime, "GetSysTime");
	it(::test_System, "System");
	it(::test_Version, "Version");
	it(::test_CriticalSection, "CriticalSection");
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

test_CriticalSection()
{
	CriticalSection("gscunit");
	EXPECT_GE(CriticalSections().size, 1);

	EnterCriticalSection("gscunit");
	sections = CriticalSections();
	EXPECT_TRUE(sections["gscunit"]);

	LeaveCriticalSection("gscunit");
	sections = CriticalSections();
	EXPECT_FALSE(sections["gscunit"]);
}
