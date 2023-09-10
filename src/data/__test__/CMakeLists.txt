if(BUILD_TESTING)
	target_sources(gsclib.Tests PRIVATE
		regex.test.c
		zip.test.c)
endif()
