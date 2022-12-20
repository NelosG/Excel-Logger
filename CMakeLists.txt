cmake_minimum_required(VERSION 3.13)
project(logger)

set(CMAKE_CXX_STANDARD 17)

configure_file(CMakeLists.txt.in OpenXLSX-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/OpenXLSX-download)

if(result)
    message(FATAL_ERROR "CMake step for OpenXLSX failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/OpenXLSX-download)

if(result)
    message(FATAL_ERROR "Build step for OpenXLSX failed: ${result}")
endif()

add_subdirectory(
        ${CMAKE_CURRENT_BINARY_DIR}/OpenXLSX-src
        ${CMAKE_CURRENT_BINARY_DIR}/OpenXLSX-build
)

add_library(logger STATIC "")

target_sources(logger PUBLIC logger.h logger.cpp)

target_include_directories(logger
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)     # For export header
target_link_libraries(logger PUBLIC OpenXLSX)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE logger)
