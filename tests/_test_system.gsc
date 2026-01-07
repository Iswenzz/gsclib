#include sr\libs\gscunit\_main;
#include sr\libs\gsclib\__test__\_suite;

main()
{
	suite("GSCLIB System");

	// System/System
	it(::test_GetSysTime, "GetSysTime");
	it(::test_System, "System");
	it(::test_Version, "Version");
	it(::test_CriticalSection, "CriticalSection");
}

test_System()
{
	EXPECT_EQ(System("cd"), 0);
}

test_GetSysTime()
{
	EXPECT_GT(GetSysTime(), 0);
}

test_Version()
{
	EXPECT_EQ(CoD4X_Version(), "21.2");
	EXPECT_EQ(GSCLIB_Version(), "2.0.0");
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
