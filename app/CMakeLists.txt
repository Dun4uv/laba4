add_executable(laba4
    laba4.cpp
    print_header/print_header.cpp
    print_header/print_header.h
    GameLoop/GameLoop.h
    GameLoop/GameLoop.cpp)

target_link_libraries(laba4 PRIVATE knightlib ioutils sfml-audio)

add_custom_command(
    TARGET laba4 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/Assets" "$<TARGET_FILE_DIR:laba4>/Assets"
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang" OR
   CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR
   CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(laba4 PRIVATE "-Wall" "-Weffc++" "-Wextra" "-Wpedantic")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    endif()
    target_compile_options(laba4 PRIVATE "/W3")
endif()
