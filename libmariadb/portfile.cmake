
if(EXISTS "${CURRENT_INSTALLED_DIR}/include/mysql/mysql.h")
	message(FATAL_ERROR "FATAL ERROR: libmysql and libmariadb are incompatible.")
endif()

vcpkg_from_github(
	OUT_SOURCE_PATH SOURCE_PATH
	REPO mariadb-corporation/mariadb-connector-c
	REF 5f7ac6b987c9563f86cf044e2198c6c4f4198f3d
	SHA512 c1304834c600156caa52689eade5e34f284683d66dcf0be2cc04a2b8cc471aed6dea7e909ba8acdf8209e37003180a6e93bf762adcc367e0a0c441c00244fd6f
	HEAD_REF 5f7ac6b987c9563f86cf044e2198c6c4f4198f3d
	PATCHES cmake.patch
)

vcpkg_cmake_configure(SOURCE_PATH "${SOURCE_PATH}")
vcpkg_cmake_install()
