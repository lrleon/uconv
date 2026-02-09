cmake_minimum_required(VERSION 3.10)

# Optional Clang helper for environments where Clang does not auto-detect
# a usable libstdc++ toolchain during compiler checks (try-compile).
set(UCONV_CLANG_GCC_INSTALL_DIR "${UCONV_CLANG_GCC_INSTALL_DIR}" CACHE STRING
    "Path passed to Clang via --gcc-install-dir (e.g. /usr/lib/gcc/x86_64-linux-gnu/13)")
set(UCONV_CLANG_GCC_TOOLCHAIN "${UCONV_CLANG_GCC_TOOLCHAIN}" CACHE STRING
    "Path passed to Clang via --gcc-toolchain (e.g. /usr)")
if(UCONV_CLANG_GCC_INSTALL_DIR)
    set(_UCONV_CLANG_GCC_FLAG "--gcc-install-dir=${UCONV_CLANG_GCC_INSTALL_DIR}")
elseif(UCONV_CLANG_GCC_TOOLCHAIN)
    set(_UCONV_CLANG_GCC_FLAG "--gcc-toolchain=${UCONV_CLANG_GCC_TOOLCHAIN}")
endif()

if(DEFINED _UCONV_CLANG_GCC_FLAG)
    set(CMAKE_C_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} ${_UCONV_CLANG_GCC_FLAG}")
    set(CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT} ${_UCONV_CLANG_GCC_FLAG}")
    set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} ${_UCONV_CLANG_GCC_FLAG}")
    set(CMAKE_SHARED_LINKER_FLAGS_INIT "${CMAKE_SHARED_LINKER_FLAGS_INIT} ${_UCONV_CLANG_GCC_FLAG}")
endif()

project(uconv CXX)

set(CMAKE_CXX_STANDARD 20)
file(STRINGS "${CMAKE_SOURCE_DIR}/version.txt" UCONV_VERSION LIMIT_COUNT 1)
if(NOT UCONV_VERSION)
    set(UCONV_VERSION "dev")
endif()

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

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if(UCONV_CLANG_GCC_INSTALL_DIR)
        message(STATUS "Using Clang gcc-install-dir: ${UCONV_CLANG_GCC_INSTALL_DIR}")
    elseif(UCONV_CLANG_GCC_TOOLCHAIN)
        message(STATUS "Using Clang gcc-toolchain: ${UCONV_CLANG_GCC_TOOLCHAIN}")
    endif()
endif()

# Generated artifacts live in the build tree.
set(UCONV_GENERATED_DIR ${CMAKE_BINARY_DIR}/generated)
set(UCONV_GENERATED_UNITS_DIR ${UCONV_GENERATED_DIR}/units)

# Sanitizers (enabled by default as in Imakefile)
option(ENABLE_SANITIZERS "Enable address and undefined sanitizers" ON)
if(ENABLE_SANITIZERS)
    add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address,undefined)
endif()

option(BUILD_DOCS "Build API documentation with Doxygen" ON)

enable_testing()

# Subdirectories
add_subdirectory(lib)
add_subdirectory(utils)
add_subdirectory(Tests)
add_subdirectory(fuzz)
add_subdirectory(Examples)

if(BUILD_DOCS)
    find_package(Doxygen QUIET)
    if(DOXYGEN_FOUND)
        set(DOXYGEN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/docs/doxygen)
        set(DOXYGEN_CONFIG_FILE ${CMAKE_BINARY_DIR}/Doxyfile)
        set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/index.html)

        configure_file(
            ${CMAKE_SOURCE_DIR}/cmake/Doxyfile.in
            ${DOXYGEN_CONFIG_FILE}
            @ONLY
        )

        add_custom_command(
            OUTPUT ${DOXYGEN_INDEX_FILE}
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIG_FILE}
            DEPENDS uconv ${DOXYGEN_CONFIG_FILE}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
        )

        add_custom_target(docs DEPENDS ${DOXYGEN_INDEX_FILE})
        message(STATUS "Doxygen docs target enabled: 'docs'")
    else()
        message(WARNING "Doxygen not found. 'docs' target will not be available.")
    endif()
endif()
