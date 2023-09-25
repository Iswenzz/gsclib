set(VCPKG_TARGET_TRIPLET x86-mingw-static)

option(BUILD_TESTING "Build tests" OFF)
if(BUILD_TESTING)
	list(APPEND VCPKG_MANIFEST_FEATURES "tests")
endif()

if(NOT DEFINED ENV{VCPKG_ROOT})
	message(FATAL_ERROR "ERROR: VCPKG_ROOT environment variable is not defined. Please set it to the root directory of your vcpkg installation.")
endif()
file(TO_CMAKE_PATH $ENV{VCPKG_ROOT} VCPKG_ROOT)
include(${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
