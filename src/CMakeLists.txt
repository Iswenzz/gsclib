add_library(gsclib OBJECT)
add_library(gsclib.Plugin SHARED)

add_subdirectory(__test__)
add_subdirectory(data)
add_subdirectory(linq)
add_subdirectory(net)
add_subdirectory(sys)
add_subdirectory(utils)

target_include_directories(gsclib PUBLIC .)
target_sources(gsclib.Plugin PRIVATE plugin.c)
target_link_libraries(gsclib.Plugin PRIVATE gsclib)

get_target_property(SOURCES gsclib SOURCES)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
