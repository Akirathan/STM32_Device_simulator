cmake_minimum_required(VERSION 3.7)
project(device_simulator)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include_directories(
    .
    communication
    http
)

set(COMMUNICATION_SOURCES
    communication/tcp_driver.cpp
    communication/client.cpp
    communication/client_timer.cpp
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

target_link_libraries(device_simulator "-lrt")