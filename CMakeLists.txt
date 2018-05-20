cmake_minimum_required(VERSION 3.7)
project(device_simulator)

set(CMAKE_CXX_STANDARD 11)

include_directories(
    .
    communication
    http
)

set(COMMUNICATION_SOURCES
    communication/tcp_driver.cpp
    communication/client.cpp
    communication/interval.cpp
    communication/interval_list.cpp
)

set(HTTP_SOURCES
    http/header.cpp
    http/header_option.cpp
    http/request.cpp
    http/response.cpp
    http/response_buffer.cpp
)

set(SOURCE_FILES
    ${COMMUNICATION_SOURCES}
    ${HTTP_SOURCES}
    main.cpp
    char_stream.cpp
    rt_assert.h
    cli.cpp
    device.cpp
    device_list.cpp
    interval_parser.cpp
)

add_executable(device_simulator ${SOURCE_FILES})