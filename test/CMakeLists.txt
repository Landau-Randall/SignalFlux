include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB TEST_SOURCES "*.cpp")

foreach(TEST_SOURCE ${TEST_SOURCES})

    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)

    add_executable(${TEST_NAME}.out ${TEST_SOURCE})

    target_link_libraries(
        ${TEST_NAME}.out
        PRIVATE
        GTest::gtest
        GTest::gtest_main 
    )
    gtest_add_tests(TARGET ${TEST_NAME}.out)

endforeach()