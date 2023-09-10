if(BUILD_TESTING)
	target_sources(gsclib.Tests PRIVATE
		main.test.c
		mock.c
		mock.h)
endif()
