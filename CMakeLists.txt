cmake_minimum_required(VERSION 3.10)
project(uconv CXX)

set(CMAKE_CXX_STANDARD 20)

# Dependencies
if(NOT DEFINED ALEPHW)
    if(DEFINED ENV{ALEPHW})
        set(ALEPHW $ENV{ALEPHW})
    else()
        message(FATAL_ERROR "ALEPHW is not defined. Please set it to the Aleph library path (e.g. cmake -DALEPHW=/path/to/aleph ..)")
    endif()
endif()

if(NOT DEFINED JSON_PATH)
    if(DEFINED ENV{JSON})
        set(JSON_PATH $ENV{JSON})
    else()
        message(FATAL_ERROR "JSON_PATH is not defined. Please set it to the nlohmann/json root path (e.g. cmake -DJSON_PATH=/path/to/json ..)")
    endif()
endif()

# Global include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${ALEPHW})
include_directories(${JSON_PATH}/include)

# Compilation options
add_compile_options(-Wall -Wextra -Wcast-align -Wno-sign-compare -Wno-write-strings -Wno-parentheses)

# Sanitizers (enabled by default as in Imakefile)
option(ENABLE_SANITIZERS "Enable address and undefined sanitizers" ON)
if(ENABLE_SANITIZERS)
    add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address,undefined)
endif()

enable_testing()

# Subdirectories
add_subdirectory(lib)
add_subdirectory(tests)
add_subdirectory(Tests)
add_subdirectory(fuzz)
add_subdirectory(Examples)
