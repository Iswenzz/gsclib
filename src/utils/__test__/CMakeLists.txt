if(BUILD_TESTING)
	target_sources(gsclib.Tests PRIVATE
		vsnprintf.test.c)
endif()
