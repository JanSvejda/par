#include <par.h>
#include <iostream>
#include <cxxtest/TestSuite.h>

using namespace std;

class ParVectorTests : public CxxTest::TestSuite
{
public:
    void testDemo( void )
    {
        TS_ASSERT( 1 + 1 > 1 );
        TS_ASSERT_EQUALS( 1 + 1, 2 );
        double * a = init_vector(1000, 10.0);
        cout << a[0] << ", " << a[10] << endl;
        delete [] a;
    }
};
