add_library(gsclib SHARED)
set_target_properties(gsclib PROPERTIES OUTPUT_NAME gsclib)

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

add_library(gsclib.Static STATIC ${SOURCES})
set_target_properties(gsclib.Static PROPERTIES OUTPUT_NAME gsclib)
target_include_directories(gsclib.Static PUBLIC .)
