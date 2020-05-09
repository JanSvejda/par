######### Tests ##########
set(CXXTEST_INCLUDE_DIR /opt/cxxtestgen)
set(CXXTEST_PYTHON_TESTGEN_EXECUTABLE /opt/cxxtestgen/bin/cxxtestgen)
find_package(CxxTest)
if(CXXTEST_FOUND)
    include_directories(${CXXTEST_INCLUDE_DIR})
    enable_testing()
    CXXTEST_ADD_TEST(unittest par_test.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/par.test.h)
    target_link_libraries(unittest par)
else()

endif()

