find_path(CURL_INCLUDE_DIRS "curl/curl.h")
find_library(CURL_LIB curl)
find_library(ZLIB_LIB NAMES zlib z)
find_package(OpenSSL REQUIRED)

set(CURL_LIBS
	${CURL_LIB}
	${ZLIB_LIB}
	openssl::openssl)

if(WIN32)
	list(APPEND CURL_LIBS winmm ws2_32 advapi32 crypt32 bcrypt)
endif()

if(UNIX)
	list(APPEND CURL_LIBS pthread)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Libcurl DEFAULT_MSG CURL_LIBS CURL_INCLUDE_DIRS)
mark_as_advanced(CURL_LIBS CURL_INCLUDE_DIRS)

if(NOT TARGET curl::curl)
	add_library(curl::curl INTERFACE IMPORTED)
    set_property(TARGET curl::curl PROPERTY INTERFACE_LINK_LIBRARIES "${CURL_LIBS}")
	set_property(TARGET curl::curl PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${CURL_INCLUDE_DIRS}")
endif()
