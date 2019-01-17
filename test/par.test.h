#include <par.h>
#include <iostream>
// #include <cxxtest/TestSuite.h>
#include <omp.h>

using namespace std;

class ParVectorTests : public CxxTest::TestSuite
{
public:
    void testDemo(void) {
        TS_ASSERT( 1 + 1 > 1 );
        TS_ASSERT_EQUALS( 1 + 1, 2 );
        double * a = init_vector(1000, 10.0);
        delete [] a;
    }

    void testOpenmp(void) {
        fork([]() {
                int thrds =  omp_get_num_threads();
                TS_ASSERT_LESS_THAN_EQUALS(2, thrds);
            }, []() {
            });
    }

    void testInit(void) {
        int n = 10;
        double* v = init_vector(n, 20.0);
        for (int i = 0; i < n; ++i)
            TS_ASSERT_EQUALS(20.0, v[i]);

        n = 50;
        double* v2 = init_vector(n, 50.0);
        for (int i = 0; i < n; ++i)
            TS_ASSERT_EQUALS(50.0, v2[i]);

        delete [] v;
        delete [] v2;
    }
};
