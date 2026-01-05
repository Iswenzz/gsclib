cmake_minimum_required(VERSION 4.2)
project(gsclib VERSION 2.0.0 LANGUAGES CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-m32 -g -mtune=core2 -fvisibility=hidden -Wno-attributes -Wno-write-strings")

# CMake
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(ClangTools)

# Dependencies
find_package(Libcurl REQUIRED)
find_package(Libmariadb REQUIRED)
find_package(Libzip REQUIRED)
find_package(PCRE2 REQUIRED)

# Tests
if(BUILD_TESTING)
	include(CTest)
	add_executable(gsclib.Tests)
	find_package(GTest CONFIG REQUIRED)
	target_link_libraries(gsclib.Tests PRIVATE
		gsclib
		GTest::gtest
		GTest::gtest_main
		GTest::gmock
		GTest::gmock_main)
	add_test(NAME Tests COMMAND gsclib.Tests)
endif()

# Build
add_subdirectory(src)
add_subdirectory(api)
