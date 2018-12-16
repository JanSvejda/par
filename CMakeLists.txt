cmake_minimum_required (VERSION 3.0)
project (ParLib VERSION 0.0.1 DESCRIPTION "Parallel Library for C++")

# set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic -Werror -fopenmp")

include_directories(include)

set(TEST_SOURCES src/test/ParallelFunctions.test.cpp)
set(LIB_SOURCES src/ParallelFunctions.cpp)

add_library(parlib STATIC ${LIB_SOURCES})
set_target_properties(parlib PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(parlib PROPERTIES PUBLIC_HEADER include/ParallelFunctions.hpp)
set_target_properties(parlib PROPERTIES SOVERSION 0)
target_include_directories(parlib PRIVATE include)
target_include_directories(parlib PRIVATE src)
include(GNUInstallDirs)

install(TARGETS parlib
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

# add_executable(test_parlib ${TEST_SOURCES})
# target_link_libraries(test_parlib parlib)
