cmake_minimum_required(VERSION 3.16.0)
project(gsclib VERSION 1.1.0 LANGUAGES C)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-m32 -Wall -O1 -s -mtune=core2")
set(CMAKE_SHARED_LINKER_FLAGS "-enable-stdcall-fixup -m32 -s -shared -static-libgcc -static-libstdc++")

# CPack
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR 7Z)
include(CPack)

# Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Tests
# include(CTest)
# add_executable(gsclib.Tests)
# target_link_libraries(gsclib.Tests PUBLIC ${CONAN_LIBS} gsclib)
# add_test(NAME Tests COMMAND gsclib.Tests)

# Build
add_subdirectory(src)
target_include_directories(gsclib PUBLIC ..)
target_link_directories(gsclib PUBLIC ..)
target_link_libraries(gsclib PUBLIC ${CONAN_LIBS} libcom_plugin)

# Pack
install(TARGETS gsclib LIBRARY DESTINATION lib)
install(DIRECTORY src/ DESTINATION lib/include/gsclib
    FILES_MATCHING PATTERN "*.hpp" PATTERN "__test__" EXCLUDE)
