
#ifndef PARFUNC_69BCD083
#define PARFUNC_69BCD083

#include <omp.h>

using namespace std;

template<typename T>
T* init_array(T* array, long long length, T value) {
    #pragma omp parallel for
    for (int i = 0; i < length; i++)
        array[i] = value;
    return array;
}

template<typename T, typename F>
T* map_array(T* array, long long length, F lambda) {
    #pragma omp parallel for
    for (int i = 0; i < length; i++)
        array[i] = lambda(array[i]);

    return array;
}

template<typename T, typename F>
T reduce_array(T* array, long long length, F lambda, T neutral) {
    T reduction = neutral;
#pragma omp parallel
    {
        T priv_part = neutral;

        #pragma omp for
        for (int i = 0; i < length; i++){
            priv_part = lambda(priv_part, array[i]);
        }

        #pragma omp critical
        {
            reduction = lambda(reduction, priv_part);
        }
    }
    return reduction;
}

template<typename T>
T* copy_array(T* array, long long length) {
    T* copy = new T[length];
#pragma omp parallel for
    for (int i = 0; i < length; i++)
        copy[i] = array[i];
    return copy;
}

template<typename T>
T* linear_transform_array(T* array, long long length, T scale, T step) {
#pragma omp parallel for
    for (int i = 0; i < length; i++)
        array[i] = scale * array[i] + step;
    return array;
}





#endif
