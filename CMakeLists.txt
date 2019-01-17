cmake_minimum_required (VERSION 3.0)
project (ParLib VERSION 0.0.1 DESCRIPTION "Parallel Library for C++")

# set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Werror -fopenmp")

include_directories(include)

set(TEST_SOURCES src/test/ParallelFunctions.test.cpp)
set(LIB_SOURCES src/ParallelFunctions.cpp)

add_library(par STATIC ${LIB_SOURCES})
set_target_properties(par PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(par PROPERTIES PUBLIC_HEADER include/par.h)
set_target_properties(par PROPERTIES SOVERSION 0)
target_include_directories(par PRIVATE include)
target_include_directories(par PRIVATE src)
include(GNUInstallDirs)

install(TARGETS par
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )


  ######### Tests ##########
  set(CXXTEST_INCLUDE_DIR /opt/cxxtestgen)
  set(CXXTEST_PYTHON_TESTGEN_EXECUTABLE /opt/cxxtestgen/bin/cxxtestgen)
find_package(CxxTest)
if(CXXTEST_FOUND)
    include_directories(${CXXTEST_INCLUDE_DIR})
    enable_testing()
    CXXTEST_ADD_TEST(unittest par_test.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/test/par.test.h)
    target_link_libraries(unittest par)
endif()


