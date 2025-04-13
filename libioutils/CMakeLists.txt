add_library(ioutils STATIC
    io_utils/io_utils.cpp
    io_utils/io_utils.h
)

target_include_directories(ioutils PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
