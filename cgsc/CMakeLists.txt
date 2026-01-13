cmake_minimum_required(VERSION 3.27)
project(CGSC VERSION 1.2.3 LANGUAGES C)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-m32 -Wall -msse2 -mfpmath=sse -Wno-packed-not-aligned -fno-omit-frame-pointer -fno-pie -O1")

# NASM
if(WIN32)
	set(CMAKE_ASM_NASM_FLAGS "-dWin32 --prefix _")
	set(CMAKE_ASM_NASM_OBJECT_FORMAT "win32")
else()
	set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf32")
endif()
enable_language(ASM_NASM)

# CMake
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(ClangTools)

# CPack
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR 7Z)
include(CPack)

# Dependencies
find_package(libuv CONFIG REQUIRED)

# Tests
if(BUILD_TESTING)
	include(CTest)
	add_executable(CGSC.Tests)
	find_path(GREATEST_INCLUDE_DIRS "greatest.h")
	target_link_libraries(CGSC.Tests PUBLIC CGSC.COD4X)
    target_include_directories(CGSC.Tests PRIVATE ${GREATEST_INCLUDE_DIRS})
	add_test(NAME Tests COMMAND CGSC.Tests)
endif()

# Build
add_library(CGSC INTERFACE)

target_include_directories(CGSC INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/CGSC>)

target_link_libraries(CGSC INTERFACE libuv::uv_a)

if(COD4X)
	add_library(CGSC.COD4X STATIC cgsc.h cod4x.h)

	add_subdirectory(asm)
	add_subdirectory(extensions)
	add_subdirectory(sys)
	add_subdirectory(utils)
	add_subdirectory(versions)

	target_link_libraries(CGSC.COD4X PUBLIC libuv::uv_a)
	target_compile_definitions(CGSC.COD4X PUBLIC COD4X18UPDATE)
	target_include_directories(CGSC.COD4X PUBLIC . .. ../version ../../plugins)
	set_target_properties(CGSC.COD4X PROPERTIES OUTPUT_NAME CGSC)
	set_target_properties(CGSC.COD4X PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ../../../lib)

	get_target_property(LIBUV_LIBRARY libuv::uv_a LOCATION)
	set(STATIC_DEPENDENCIES ${LIBUV_LIBRARY})

	foreach(dependency ${STATIC_DEPENDENCIES})
		add_custom_command(TARGET CGSC.COD4X POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy ${dependency} ../../../lib)
	endforeach()
endif()

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

# Install
install(TARGETS CGSC LIBRARY DESTINATION lib)
install(DIRECTORY . DESTINATION include/CGSC FILES_MATCHING PATTERN "*.h" PATTERN "__test__" EXCLUDE)

# Package
include(CMakePackageConfigHelpers)

configure_package_config_file(cmake/CGSCConfig.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/CGSCConfig.cmake"
	INSTALL_DESTINATION lib/cmake/CGSC)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/CGSCConfig.cmake"
    DESTINATION lib/cmake/CGSC)
