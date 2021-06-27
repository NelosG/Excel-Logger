# Excel-Logger

Simple logger that writes your data to an Excel table.

## Usage: 
- Create CMakeLists.txt.in with following text:
```    cmake_minimum_required(VERSION 3.13)
    
    project(Excel-Logger-download NONE)
    
    include(ExternalProject)

    ExternalProject_Add(Excel-Logger
        GIT_REPOSITORY    https://github.com/NelosG/Excel-Logger.git
        GIT_TAG           master
        SOURCE_DIR        "${CMAKE_CURRENT_BINARY_DIR}/Excel-Logger-src"
        BINARY_DIR        "${CMAKE_CURRENT_BINARY_DIR}/Excel-Logger-build"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND     ""
        INSTALL_COMMAND   ""
        TEST_COMMAND      ""
    )
```

Put the following code in your CMakeLists.txt:
```
    configure_file(CMakeLists.txt.in Excel-Logger-download/CMakeLists.txt)

    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Excel-Logger-download)

    if (result)
        message(FATAL_ERROR "CMake step for Excel-Logger failed: ${result}")
    endif ()

    execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Excel-Logger-download)

    if (result)
        message(FATAL_ERROR "Build step for Excel-Logger failed: ${result}")
    endif ()

    add_subdirectory(
        ${CMAKE_CURRENT_BINARY_DIR}/Excel-Logger-src
        ${CMAKE_CURRENT_BINARY_DIR}/Excel-Logger-build
    )
    
    ................
    
    target_link_libraries(<Your_Target> <PUBLIC | PRIVATE> logger)
```
