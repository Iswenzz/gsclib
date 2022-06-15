#include sr\libs\gscunit\_main;
#include sr\libs\gsclib\__test__\_suite;

main()
{
	suite("GSCLIB Data");
	beforeAll();

	// data/file
	it(::test_FILE_Create, "FILE_Create");
	it(::test_FILE_Open, "FILE_Open");
	it(::test_FILE_Exists, "FILE_Exists");
	it(::test_FILE_Seek, "FILE_Seek");
	it(::test_FILE_Write, "FILE_Write");
	it(::test_FILE_Read, "FILE_Read");
	it(::test_FILE_WriteLine, "FILE_WriteLine");
	it(::test_FILE_ReadLine, "FILE_ReadLine");
	it(::test_FILE_Close, "FILE_Close");
	it(::test_FILE_Delete, "FILE_Delete");
	it(::test_FILE_MkDir, "FILE_MkDir");
	it(::test_FILE_ReadDir, "FILE_ReadDir");
	it(::test_FILE_RmDir, "FILE_RmDir");

	// data/regex
	it(::test_RegexMatch, "RegexMatch");
	it(::test_RegexReplace, "RegexReplace");
	it(::test_RegexSplit, "RegexSplit");

	// data/zip
	it(::test_ZIP_Open, "ZIP_Open");
	it(::test_ZIP_Add, "ZIP_Add");
	it(::test_ZIP_Rename, "ZIP_Rename");
	it(::test_ZIP_Delete, "ZIP_Delete");
	it(::test_ZIP_Close, "ZIP_Close");
}

beforeAll()
{
	if (!FILE_Exists("temp"))
		FILE_MkDir("temp");
}

test_FILE_MkDir()
{
	EXPECT_TRUE(FILE_MkDir("mkdir"));
}

test_FILE_RmDir()
{
	EXPECT_TRUE(FILE_RmDir("mkdir"));
}

test_FILE_ReadDir()
{
	FILE_Create("mkdir/a.txt");
	FILE_Create("mkdir/b.txt");

	dir = FILE_ReadDir("mkdir");

	EXPECT_EQ(dir.size, 2);
	EXPECT_CONTAIN(dir, "a.txt");
	EXPECT_CONTAIN(dir, "b.txt");
}

test_FILE_Create()
{
	EXPECT_TRUE(FILE_Create("temp/test.txt"));
}

test_FILE_Open()
{
	level.tests.file = FILE_Open("temp/test.txt", "w+");
	EXPECT_TRUE(level.tests.file);
}

test_FILE_Close()
{
	EXPECT_TRUE(FILE_Close(level.tests.file));
}

test_FILE_Exists()
{
	EXPECT_TRUE(FILE_Exists("temp/test.txt"));
	EXPECT_FALSE(FILE_Exists("temp/notFound.txt"));
}

test_FILE_Seek()
{
	EXPECT_TRUE(FILE_Seek(level.tests.file, 0));
}

test_FILE_ReadLine()
{
	FILE_Seek(level.tests.file, 0);
	EXPECT_EQ(FILE_ReadLine(level.tests.file), "test");
}

test_FILE_WriteLine()
{
	EXPECT_TRUE(FILE_WriteLine(level.tests.file, "%s", "newline"));
}

test_FILE_Read()
{
	FILE_Seek(level.tests.file, 0);
	EXPECT_EQ(FILE_Read(level.tests.file), "test\ntest\n");
}

test_FILE_Write()
{
	EXPECT_TRUE(FILE_Write(level.tests.file, "%s\n%s\n", "test", "test"));
}

test_FILE_Delete()
{
	EXPECT_TRUE(FILE_Delete("temp/test.txt"));
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

test_ZIP_Open()
{
	level.tests.zipFile = ZIP_Open("temp/test.zip");
	EXPECT_TRUE(level.tests.zipFile);
}

test_ZIP_Close()
{
	EXPECT_TRUE(ZIP_Close(level.tests.zipFile));
	FILE_Delete("temp/test.zip");
	FILE_Delete("temp/test.txt");
}

test_ZIP_Add()
{
	FILE_Create("temp/test.txt");
	EXPECT_TRUE(ZIP_Add(level.tests.zipFile, "temp/test.txt", "test.txt"));
	EXPECT_TRUE(ZIP_Add(level.tests.zipFile, "temp/test.txt", "delete.txt"));
}

test_ZIP_Rename()
{
	EXPECT_TRUE(ZIP_Rename(level.tests.zipFile, "test.txt", "test_new.txt"));
}

test_ZIP_Delete()
{
	EXPECT_TRUE(ZIP_Delete(level.tests.zipFile, "delete.txt"));
}
