add_library(knightlib STATIC
    Knight/Knight.cpp
    Knight/Knight.h
    Battle/Battle.cpp
    Battle/Battle.h
)

target_include_directories(knightlib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(knightlib PRIVATE ioutils)
