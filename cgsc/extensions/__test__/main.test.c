#include <greatest.h>

GREATEST_MAIN_DEFS();

extern SUITE(Suite_utils);

int main(int argc, char** argv)
{
	GREATEST_MAIN_BEGIN();

	RUN_SUITE(Suite_utils);

	GREATEST_MAIN_END();
}
