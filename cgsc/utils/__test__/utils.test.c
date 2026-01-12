#include "utils/utils.h"

#include <greatest.h>

TEST test_fmt()
{
	ASSERT_STR_EQ(fmt("test"), "test");
	ASSERT_STR_EQ(fmt("test %d", 1), "test 1");
	ASSERT_STR_EQ(fmt("%s %d", "test", 2), "test 2");

	PASS();
}

SUITE(Suite_utils)
{
	RUN_TEST(test_fmt);
}
