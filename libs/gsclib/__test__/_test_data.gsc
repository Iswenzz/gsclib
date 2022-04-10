#include libs\gscunit\_main;
#include libs\gsclib\__test__\_suite;

main()
{
	suite("GSCLIB - Data");

	// data/regex
	it(::test_RegexMatch, "RegexMatch");
	it(::test_RegexReplace, "RegexReplace");
	it(::test_RegexSplit, "RegexSplit");

	// data/zip
	it(::test_zipOpen, "ZIP_Open");
	it(::test_zipAdd, "ZIP_Add");
	it(::test_zipRename, "ZIP_Rename");
	it(::test_zipDelete, "ZIP_Delete");
	it(::test_zipClose, "ZIP_Close");
}

test_RegexMatch()
{
	matches = RegexMatch("hello123world456", "\\d+");
	EXPECT_CONTAIN(matches, "123");
	EXPECT_CONTAIN(matches, "456");

	emailPattern = "^([a-z0-9\\+_\\-]+)(\\.[a-z0-9\\+_\\-]+)*@([a-z0-9\\-]+\\.)+[a-z]{2,6}$";
	matches = RegexMatch("suxlolz1528@gmail.com", emailPattern);
	EXPECT_CONTAIN(matches, "suxlolz1528@gmail.com");
}

test_RegexSplit()
{
	matches = RegexSplit("hello123world456", "\\d+");
	EXPECT_CONTAIN(matches, "hello");
	EXPECT_CONTAIN(matches, "world");
}

test_RegexReplace()
{
	EXPECT_EQ(RegexReplace("123hello456world789", "_", "\\d+"), "_hello_world_");
}

test_zipOpen()
{
	level.tests.zipFile = ZIP_Open("temp/test.zip");
	EXPECT_TRUE(level.tests.zipFile);
}

test_zipClose()
{
	EXPECT_TRUE(ZIP_Close(level.tests.zipFile));
}

test_zipAdd()
{
	EXPECT_TRUE(ZIP_Add(level.tests.zipFile, "localization.txt", "localization.txt"));
	EXPECT_TRUE(ZIP_Add(level.tests.zipFile, "localization.txt", "delete.txt"));
}

test_zipRename()
{
	ZIP_Delete(level.tests.zipFile, "localization_new.txt");
	EXPECT_TRUE(ZIP_Rename(level.tests.zipFile, "localization.txt", "localization_new.txt"));
}

test_zipDelete()
{
	EXPECT_TRUE(ZIP_Delete(level.tests.zipFile, "delete.txt"));
}
