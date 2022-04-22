#include "data/zip.h"

#include <greatest.h>
#include <stdlib.h>

static zip_t* zipFile;

TEST test_zipVersion()
{
	ASSERT_STR_EQ(zip_libzip_version(), "1.8.0");
	PASS();
}

TEST test_zipOpen()
{
	zipFile = ZIP_Open("bin/test.zip");

	ASSERT(zipFile);
	PASS();
}

TEST test_zipClose()
{
	ASSERT(ZIP_Close(zipFile));
	PASS();
}

TEST test_zipAdd()
{
	ASSERT(ZIP_Add(zipFile, "conaninfo.txt", "conaninfo.txt"));
	ASSERT(ZIP_Add(zipFile, "conaninfo.txt", "delete.txt"));
	PASS();
}

TEST test_zipRename()
{
	ZIP_Delete(zipFile, "conaninfo_new.txt");
	ASSERT(ZIP_Rename(zipFile, "conaninfo.txt", "conaninfo_new.txt"));
	PASS();
}

TEST test_zipDelete()
{
	ASSERT(ZIP_Delete(zipFile, "delete.txt"));
	PASS();
}

SUITE(Suite_data_zip)
{
	RUN_TEST(test_zipVersion);
	RUN_TEST(test_zipOpen);
	RUN_TEST(test_zipAdd);
	RUN_TEST(test_zipRename);
	RUN_TEST(test_zipDelete);
	RUN_TEST(test_zipClose);
}
