cmake_minimum_required(VERSION 3.13)
project(logger)

set(CMAKE_CXX_STANDARD 17)

set(LOGGER_SOURCE logger.h logger.cpp)


set(SOURCE_FOR_OpenXLSX ${CMAKE_CURRENT_BINARY_DIR}/OpenXLSX)

configure_file(CMakeLists.txt.in OpenXLSX-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/OpenXLSX-download )
if(result)
    message(FATAL_ERROR "CMake step for OpenXLSX failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/OpenXLSX-download )
if(result)
    message(FATAL_ERROR "Build step for OpenXLSX failed: ${result}")
endif()

add_subdirectory(
        ${SOURCE_FOR_OpenXLSX}
)

add_library(logger-static STATIC "")
target_sources(logger-static PUBLIC ${LOGGER_SOURCE})
target_include_directories(logger-static
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)     # For export header
target_link_libraries(logger-static PUBLIC OpenXLSX-shared)
