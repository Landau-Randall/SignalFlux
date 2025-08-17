include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB TEST_SOURCES "*.cpp")

add_executable(run_tests ${TEST_SOURCES})

target_link_libraries(
    run_tests
    PRIVATE
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_add_tests(TARGET run_tests)