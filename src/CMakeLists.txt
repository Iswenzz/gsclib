add_library(gsclib SHARED)

add_subdirectory(Game)
add_subdirectory(IO)
add_subdirectory(Network)
add_subdirectory(System)
add_subdirectory(Utils)

# Build
target_sources(gsclib PRIVATE main.cpp Base.hpp)
target_precompile_headers(gsclib PRIVATE Base.hpp)
target_include_directories(gsclib PUBLIC . ../..)

set_target_properties(gsclib PROPERTIES
	PREFIX ""
	OUTPUT_NAME gsclib
	LIBRARY_OUTPUT_DIRECTORY ../../../../bin
	RUNTIME_OUTPUT_DIRECTORY ../../../../bin)

target_link_libraries(gsclib PUBLIC
	$<$<BOOL:${WIN32}>:com_plugin>
	$<$<BOOL:${UNIX}>:m>
	libcurl::libcurl
	libmariadb::libmariadb
	libzip::libzip
	PCRE2::PCRE2)

target_link_directories(gsclib PUBLIC ../..)

# Tree
get_target_property(SOURCES gsclib SOURCES)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
