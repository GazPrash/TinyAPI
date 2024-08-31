find_package(CURL REQUIRED)

add_executable(
    hello_test
    test1.cpp
)
target_link_libraries(hello_test
    TinyApi
    GTest::gtest_main
    CURL::libcurl
)

include(GoogleTest)
gtest_discover_tests(hello_test)
