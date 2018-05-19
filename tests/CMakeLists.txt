set( TEST_NAME unit )

add_executable( ${TEST_NAME}
    random_bytes.cpp
    main.cpp
)

target_compile_options( ${TEST_NAME} PRIVATE ${ROMZ_CXX_FLAGS} )

target_include_directories( ${TEST_NAME} PRIVATE 
        ${PROJECT_SOURCE_DIR}/src
    #    ${PROJECT_SOURCE_DIR}/include
    #    ${PROJECT_SOURCE_DIR}
)

target_link_libraries( ${TEST_NAME} 
    -fprofile-arcs 
    gtest 
    gtest_main 
    random-bytes
    #    -lboost_system
    #    -lboost_thread
    #    -lboost_filesystem
    -lpthread 
    -ldl
)

add_test( NAME ${TEST_NAME} COMMAND ${TEST_NAME} )

