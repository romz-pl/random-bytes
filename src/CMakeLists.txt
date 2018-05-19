
set( LIB_NAME random-bytes )

add_library( ${LIB_NAME} STATIC
    random_bytes.cpp
)

target_include_directories( ${LIB_NAME} PRIVATE 
    #    ${PROJECT_SOURCE_DIR}/src 
    #    ${PROJECT_SOURCE_DIR}/include
)

target_compile_options( ${LIB_NAME} PRIVATE ${ROMZ_CXX_FLAGS} )


