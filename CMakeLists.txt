cmake_minimum_required(VERSION 3.12)

project("laba4" CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/utf-8)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
)

set(SFML_BUILD_AUDIO TRUE)
set(SFML_BUILD_GRAPHICS FALSE)
set(SFML_BUILD_WINDOW FALSE)
set(SFML_BUILD_NETWORK FALSE)

FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(libioutils) 
add_subdirectory(libknight)
add_subdirectory(app)
add_subdirectory(tests)

add_dependencies(laba4 knightlib ioutils)
add_dependencies(laba4_tests knightlib ioutils)

if(WIN32)
    add_custom_target(run_laba4
        COMMAND cmd /C "chcp 65001 > nul && $<TARGET_FILE:laba4>"
        DEPENDS laba4
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/app
    )

    add_custom_target(run_tests
        COMMAND cmd /C "chcp 65001 > nul && ${CMAKE_CTEST_COMMAND}"
        DEPENDS laba4_tests
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
else()
    add_custom_target(run_laba4
        COMMAND $<TARGET_FILE:laba4>
        DEPENDS laba4
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/app
    )

    add_custom_target(run_tests
        COMMAND ${CMAKE_CTEST_COMMAND}
        DEPENDS laba4_tests
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()
