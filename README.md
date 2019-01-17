# Par
A collection of parallel OpenMP functions.

# Installation
Go to the root of the project's directory and execute the following:

```
mkdir build; cd build
cmake ..
sudo make install
```

This will install two things on your system: /usr/local/lib/libpar.a and /usr/local/include/par.h

# Usage
After you have installed the library, you can include it in your C++ project (`#include <par.h>`).
To take advantage of multithreading you will need to compile your program with OpenMP (for `g++`
you do that by simply adding the `-fopenmp` flag).
