find_path(OPENSSL_INCLUDE_DIRS "openssl/ssl.h")
find_library(LIBCRYPTO_LIB crypto)
find_library(OPENSSL_LIB ssl)
find_library(ZLIB_LIB NAMES zlib z)

set(OPENSSL_LIBS
	${OPENSSL_LIB}
	${LIBCRYPTO_LIB}
	${ZLIB_LIBRARY})

if(WIN32)
	list(APPEND OPENSSL_LIBS ws2_32 gdi32 crypt32)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(OpenSSL DEFAULT_MSG OPENSSL_LIBS OPENSSL_INCLUDE_DIRS)
mark_as_advanced(OPENSSL_LIBS OPENSSL_INCLUDE_DIRS)

if(NOT TARGET openssl::openssl)
	add_library(openssl::openssl INTERFACE IMPORTED)
    set_property(TARGET openssl::openssl PROPERTY INTERFACE_LINK_LIBRARIES "${OPENSSL_LIBS}")
	set_property(TARGET openssl::openssl PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${OPENSSL_INCLUDE_DIRS}")
endif()
