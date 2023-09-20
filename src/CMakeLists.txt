add_library(gsclib SHARED)

add_subdirectory(__test__)
add_subdirectory(data)
add_subdirectory(linq)
add_subdirectory(net)
add_subdirectory(sys)
add_subdirectory(utils)

target_include_directories(gsclib PUBLIC .)
target_sources(gsclib PRIVATE plugin.c)
get_target_property(SOURCES gsclib SOURCES)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

if(BUILD_TESTING)
	target_sources(gsclib.Lib PRIVATE ${SOURCES})
endif()
