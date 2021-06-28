# Excel-Logger

Simple logger that writes your data to an Excel table.

## Usage: 
- Create CMakeLists.txt.in with following text:
```    
    cmake_minimum_required(VERSION 3.13)
    
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

    cmake_minimum_required(VERSION ...)
    project(<Name>)

    set(CMAKE_CXX_STANDARD <...>)
    
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY <Yuor_Output_Dir)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY <Yuor_Output_Dir)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY <Yuor_Output_Dir)
    
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
    
    <Your Cmake Code...>
    
    target_link_libraries(<Your_Target> <PUBLIC | PRIVATE> logger)
```

## Example:
```
    #include "logger.h"
    
    int main() {
        logger lg("../test.xlsx");  // the path must ends with <filename>.xlsx
    
        lg.set_page("Test");       // be sure that you set at least 1 page
        
        lg.set_heading({"1,2,3"});  // set your heading at row 0
                                    // does not reset the position
    
        lg.write("Hello", 2, 3); // writes each object passed by comma into a separate
                                    // cell of the table (starting from the current position)
                                    // does not reset the position after the end of the recording
    
        lg.next_line( );            // sets position to (current_row + 1, 0)
    
    
        lg.writeln("Hello", 2, 3);   //  same as 'lg.write("Hello", 2, 3); lg.next_line();'
    
        lg << "Hello" << 2 << 3;        // same as 'lg.write("Hello", 2, 3);'
    
        lg << "Hello" << 2 << 3 << '\n'; // same as 'lg.writeln("Hello", 2, 3);'
    
        lg.flush( );    // saves current changes in doc
    
        lg.close( );    // save doc and puts the logger in a closed state (also called when the destructor is called
                        // if you forgot to call it)
    }
```
