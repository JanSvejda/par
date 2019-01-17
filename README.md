# Par
A collection of parallel OpenMP utility functions for vectors and matrices in C++.

# Installation
Go to the root of the project's directory and execute the following:

```
mkdir build; cd build
cmake ..
sudo make install
```

This will install two things on your system: `/usr/local/lib/libpar.a` and `/usr/local/include/par.h`

# Usage
After you have installed the library, you can include it in your C++ project (`#include <par.h>`).
To take advantage of multithreading you will need to compile your program with OpenMP (for `g++`
you do that by simply adding the `-fopenmp` flag).

# Testing
The library uses CxxTest suite for unit testing. CMake is set up to find the framework under `/opt`, so
beware of that. Otherwise, the executable for running test is not generated during `sudo make install`.

To see the results just run `make test` in the build directory. You can have a look then in the subfolder
`Testing/Temporary` at the log files generated during the tests.
