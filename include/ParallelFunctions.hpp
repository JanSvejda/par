
#ifndef PARFUNC_69BCD083
#define PARFUNC_69BCD083

#include <omp.h>
#include <iostream>

using namespace std;

template<typename T>
T* init_array(T* array, long long length, T value) {
    #pragma omp parallel for
    for (int i = 0; i < length; ++i)
        array[i] = value;
    return array;
}

template<typename T, typename F>
T* map_array(T* array, long long length, F lambda) {
    #pragma omp parallel for
    for (int i = 0; i < length; ++i)
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
        for (int i = 0; i < length; ++i){
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
    for (int i = 0; i < length; ++i)
        copy[i] = array[i];
    return copy;
}

template<typename T>
T* linear_transform_array(T* array, long long length, T scale, T step) {
#pragma omp parallel for
    for (int i = 0; i < length; ++i)
        array[i] = scale * array[i] + step;
    return array;
}

template<typename T>
T** init_matrix(T** matrix, long long dims[], T& value) {
    long long d1 = dims[0], d2 = dims[1];
#pragma omp parallel for collapse(2)
    for (int i = 0; i < d1; ++i)
        for (int j = 0; j < d2; ++j)
            matrix[i][j] = value;
    return matrix;
}

template<typename T>
T** init_matrix(long long dims[], T value) {
    long long d1 = dims[0], d2 = dims[1];
    T ** matrix = new T*[d1];
    #pragma omp parallel for
    for (int i = 0; i < d1; ++i){
        matrix[i] = new T[d2];
        #pragma omp parallel for
        for (int j = 0; j < d2; ++j)
            matrix[i][j] = value;
    }
    return matrix;
}

template<typename T>
T** copy_matrix(T** matrix, long long dims[]) {
    long long d1 = dims[0], d2 = dims[1];
    T** copy = new T[d1];
#pragma omp parallel for
    for (int i = 0; i < d1; ++i) {
        copy[i] = new T[d2];
        for (int j = 0; j < d2; ++j)
            copy[i][j] = matrix[i][j];
    }
    return copy;
}

template<typename T, typename F>
T** map_matrix(T** matrix, long long dims[], F lambda) {
    long long d1 = dims[0], d2 = dims[1];
#pragma omp parallel for collapse(2)
    for (int i = 0; i < d1; ++i)
        for (int j = 0; j < d2; ++j)
            matrix[i][j] = lambda(matrix[i][j]);

    return matrix;
}

template<typename T>
void print_matrix(T** m, long long dims[]) {
    long long d1 = dims[0], d2 = dims[1];
    for (int i = 0; i < d1; ++i){
        for (int j = 0; j < d2; ++j)
            cout << m[i][j] << " ";
        cout << endl;
    }

}


template<typename T, typename F>
T** wave_matrix(T** matrix, long long N, F lambda) {
    long long x, y;
    long long dims[2] = {N, N};

    for (long long i = 1; i < N; ++i){ // i is the i-th wave
        #pragma omp parallel for private(x,y)
        for (y = 1; y <= i; ++y){
            x = i+1 - y;
            matrix[x][y] = lambda(matrix[x-1][y], matrix[x][y-1], matrix[x][y]);
        }
        // barrier
        print_matrix(matrix, dims);
        cout << "=============================================" << endl;
    }

    for (long long i = 2; i < N; ++i){
        #pragma omp parallel for private(x,y)
        for (y = i; y < N; ++y) {
            x = N-1+i - y;
            matrix[x][y] = lambda(matrix[x-1][y], matrix[x][y-1], matrix[x][y]);
        }
        // barrier
        print_matrix(matrix, dims);
        cout << "=============================================" << endl;
    }

}

template<typename T>
void destroy_matrix(T** m, long long dims[]) {
    long long d1 = dims[0], d2 = dims[1];

    for (int i = 0; i < d1; ++i)
        delete [] m[i];
    delete [] m;
}

#endif
