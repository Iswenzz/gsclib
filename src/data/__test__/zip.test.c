#include "data/zip.h"

#include <greatest.h>
#include <stdlib.h>

static zip_t* zipFile;

TEST test_zipVersion()
{
	ASSERT_STR_EQ(zip_libzip_version(), "1.9.2");
	PASS();
}

TEST test_zipOpen()
{
	zipFile = ZIP_Open("test.zip");

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
	ASSERT(ZIP_Add(zipFile, "cmake_install.cmake", "cmake_install.cmake"));
	ASSERT(ZIP_Add(zipFile, "cmake_install.cmake", "delete.txt"));
	PASS();
}

TEST test_zipRename()
{
	ZIP_Delete(zipFile, "cmake_install_new.cmake");
	ASSERT(ZIP_Rename(zipFile, "cmake_install.cmake", "cmake_install_new.cmake"));
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
