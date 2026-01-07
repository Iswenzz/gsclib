find_path(LIBMARIADB_INCLUDE_DIR "mysql/mysql.h")
find_path(LIBMARIADB_CPP_INCLUDE_DIR "mariadb/conncpp.hpp")
find_library(LIBMARIADB_LIB mariadb)
find_library(LIBMARIADBCPP_LIB mariadbcpp-static)
find_library(ZLIB_LIB NAMES zlib z)

set(LIBMARIADB_LIBS
	${LIBMARIADBCPP_LIB}
	${LIBMARIADB_LIB}
	${ZLIB_LIB})

set(LIBMARIADB_INCLUDE_DIRS
	${LIBMARIADB_CPP_INCLUDE_DIR}
	${LIBMARIADB_CPP_INCLUDE_DIR}/mariadb
	${LIBMARIADB_INCLUDE_DIR}
	${LIBMARIADB_INCLUDE_DIR}/mysql)

if(WIN32)
	list(APPEND LIBMARIADB_LIBS shlwapi)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Libmariadb DEFAULT_MSG LIBMARIADB_LIBS LIBMARIADB_INCLUDE_DIRS)
mark_as_advanced(LIBMARIADB_LIBS LIBMARIADB_INCLUDE_DIRS)

if(NOT TARGET libmariadb::libmariadb)
	add_library(libmariadb::libmariadb INTERFACE IMPORTED)
    set_property(TARGET libmariadb::libmariadb PROPERTY INTERFACE_LINK_LIBRARIES "${LIBMARIADB_LIBS}")
	set_property(TARGET libmariadb::libmariadb PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${LIBMARIADB_INCLUDE_DIRS}")
endif()
