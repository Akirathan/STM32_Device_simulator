cmake_minimum_required(VERSION 3.7)
project(device_simulator)

set(CMAKE_CXX_STANDARD 11)

include_directories(
    .
    http
)

set(HTTP_SOURCES
    http/header.cpp
    http/header_option.cpp
    http/request.cpp
    http/response.cpp
    http/response_parser.cpp
)

set(SOURCE_FILES
    ${HTTP_SOURCES}
    main.cpp
    char_stream.cpp
    rt_assert.h
)

add_executable(device_simulator ${SOURCE_FILES})