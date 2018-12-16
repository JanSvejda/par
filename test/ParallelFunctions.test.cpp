#include <parlib>
#include <iostream>

using namespace std;

int main () {
    double * a = init_array(new double[1000], 10, 1000);
    cout << a[0] << ", " << a[10] << endl;
}
