find_path(CURL_INCLUDE_DIR "curl/curl.h")
find_library(CURL_LIB curl)
find_library(LIBSSH2_LIB ssh2)
find_library(ZLIB_LIB NAMES zlib z)

set(CURL_LIBS
	${CURL_LIB}
	${ZLIB_LIB}
	${LIBSSH2_LIB})

set(CURL_INCLUDE_DIRS
	${CURL_INCLUDE_DIR}
	${CURL_INCLUDE_DIR}/curl)

if(WIN32)
	list(APPEND CURL_LIBS bcrypt)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Libcurl DEFAULT_MSG CURL_LIBS CURL_INCLUDE_DIRS)
mark_as_advanced(CURL_LIBS CURL_INCLUDE_DIRS)

if(NOT TARGET libcurl::libcurl)
	add_library(libcurl::libcurl INTERFACE IMPORTED)
    set_property(TARGET libcurl::libcurl PROPERTY INTERFACE_LINK_LIBRARIES "${CURL_LIBS}")
	set_property(TARGET libcurl::libcurl PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${CURL_INCLUDE_DIRS}")
endif()
