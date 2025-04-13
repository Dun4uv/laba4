add_executable(laba4_tests
    knight_test.cpp
)

target_include_directories(laba4_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/libknight 
)

target_link_libraries(laba4_tests PRIVATE knightlib ioutils gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(laba4_tests)
