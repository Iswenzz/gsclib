file(TO_CMAKE_PATH $ENV{VCPKG_ROOT} VCPKG_ROOT)
set(VCPKG_TARGET_TRIPLET x86-mingw-static)

option(BUILD_TESTING "Build tests" OFF)
if(BUILD_TESTING)
	list(APPEND VCPKG_MANIFEST_FEATURES "tests")
endif()

include(${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
