set(VCPKG_TARGET_ARCHITECTURE x86)
set(VCPKG_CRT_LINKAGE static)
set(VCPKG_LIBRARY_LINKAGE static)
set(VCPKG_ENV_PASSTHROUGH PATH)
set(VCPKG_C_FLAGS "-Wno-incompatible-pointer-types -std=c17")
set(VCPKG_CXX_FLAGS "-Wno-incompatible-pointer-types -std=c17")

set(VCPKG_CMAKE_SYSTEM_NAME MinGW)
set(VCPKG_BUILD_TYPE release)
