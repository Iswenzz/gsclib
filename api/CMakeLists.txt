target_sources(gsclib PRIVATE gsclib.hpp)
target_include_directories(gsclib PRIVATE .)

add_custom_target(api
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/api/_gsclib.asm" "${CMAKE_SOURCE_DIR}/../../src/asmsource"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/api/gsclib.cpp" "${CMAKE_SOURCE_DIR}/../../src"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/api/gsclib.hpp" "${CMAKE_SOURCE_DIR}/../../src")
