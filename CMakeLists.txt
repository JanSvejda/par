cmake_minimum_required(VERSION 3.0)
project(ParLib VERSION 0.0.1 DESCRIPTION "Library of Parallel Functions for C++")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Werror -fopenmp")

set(header_files
        ${CMAKE_CURRENT_SOURCE_DIR}/par/par.hpp
        )

add_library(par INTERFACE)
target_include_directories(par INTERFACE par)
target_sources(par INTERFACE "$<BUILD_INTERFACE:${header_files}>")
target_include_directories(par INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/par/>)
target_include_directories(par SYSTEM INTERFACE $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/par>)
target_compile_definitions(par INTERFACE)

# Setup package config
include(CMakePackageConfigHelpers)
set(CONFIG_PACKAGE_INSTALL_DIR lib/cmake/par)

write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/par-config-version.cmake
        VERSION 0.0.1
        COMPATIBILITY SameMajorVersion
)

# Install target
install(DIRECTORY par DESTINATION include)


option(PAR_BUILD_TEST_EXAMPLE "build test and example" ON)
if (${PAR_BUILD_TEST_EXAMPLE})
    enable_testing()
    add_subdirectory(examples/)
    add_subdirectory(test/)
endif ()
#
#option(PAR_BUILD_DOC "generate documentation" OFF)
#if(PAR_BUILD_DOC)
#    add_subdirectory(doc/)
#endif()
