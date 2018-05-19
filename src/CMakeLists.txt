
set( LIB_NAME random-bytes )


find_package( OpenSSL REQUIRED )

add_library( ${LIB_NAME} STATIC
    random_bytes.cpp
)

target_include_directories( ${LIB_NAME} PRIVATE 
    #    ${PROJECT_SOURCE_DIR}/src 
    #    ${PROJECT_SOURCE_DIR}/include
)

target_compile_options( ${LIB_NAME} PRIVATE ${ROMZ_CXX_FLAGS} )

target_include_directories( ${LIB_NAME} PUBLIC ${OPENSSL_INCLUDE_DIR} )

target_link_libraries( ${LIB_NAME} PUBLIC ${OPENSSL_CRYPTO_LIBRARY} )
