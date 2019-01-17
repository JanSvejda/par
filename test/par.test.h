#include <par.h>
#include <iostream>
#include <cxxtest/TestSuite.h>
#include <omp.h>
#include <string>

using namespace std;

class ParVectorTests : public CxxTest::TestSuite
{
public:
    void testDemo() {
        TS_ASSERT( 1 + 1 > 1 );
        TS_ASSERT_EQUALS( 1 + 1, 2 );
        double * a = init_vector(1000, 10.0);
        delete [] a;
    }

    void testOpenmp() {
        fork([]() {
                int thrds =  omp_get_num_threads();
                TS_ASSERT_LESS_THAN_EQUALS(2, thrds);
            }, []() {
            });
    }

    void testInit() {
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

    void testInitLambda() {
        long long n = 2000;
        int* v = init_vector_l<int>(n, [](long long i) { return i; });

        for (int i = 0; i < n; ++i)
            TS_ASSERT_EQUALS(v[i], i);
        delete [] v;
    }

    void testMapVector() {
        long long n = 2000;
        string* v = init_vector(n, string("Hello"));
        map_vector(v, n, [](string s) { return s + ", there"; });

        for (int i = 0; i < n; ++i)
            TS_ASSERT_EQUALS(v[i], string("Hello, there"));

        delete [] v;
    }

    void testReduceVector() {
        long long n = 3577;
        int* v = init_vector(n, 1);

        int reduction = reduce_vector(v, n, [](int acc, int val) {return acc + val;}, 0);
        TS_ASSERT_EQUALS(reduction, 3577);

        v[27] = 1234;
        reduction = reduce_vector(v, n, [](int acc, int val) {return acc < val ? val : acc;}, 0);
        TS_ASSERT_EQUALS(reduction, 1234);

        delete [] v;
    }

    void testCopyVector() {
        long long n = 2000;
        int* v = init_vector_l<int>(n, [](long long i) { return -i; });

        for (int i = 0; i < n; ++i)
            TS_ASSERT_EQUALS(v[i], -i);

        int * vc = copy_vector(v, n);
        for (int i = 0; i < n; ++i)
            TS_ASSERT_EQUALS(vc[i], -i);
        delete [] v;
        delete [] vc;
    }

    void testTransformVector() {
        long long n = 9842;
        int* v = init_vector_l<int>(n, [](long long i) { return -i; });

        for (int i = 0; i < n; ++i)
            TS_ASSERT_EQUALS(v[i], -i);

        linear_transform_vector(v, n, -1, 2);
        for (int i = 0; i < n; ++i)
            TS_ASSERT_EQUALS(v[i], i+2);

        delete [] v;
    }
};
