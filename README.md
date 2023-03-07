# CSE 282 Final Project

Solving combinatorial selection of nutrients to treat patients with low
abundance microbes

## Requirements

1. Clang or GCC C++ compiler (Clang preferred)
2. CMake
3. Armadillo linear algebra library

### Installing requirements

For macOS with homebrew

```sh
brew install cmake armadillo
```

## Compiling

1. Create the build folder

```sh
mkdir build
cd build
```

2. Configure the project

```sh
export CC=clang
export CXX=clang++
cmake -DCMAKE_BUILD_TYPE=Release ..
```

3. Build the project

```sh
cmake --build .
```

## Testing

We integrated Catch2 framework with CTest. To run the test, the following
command can be used.

```sh
# In the build folder
ctest
```

## Author

1. Pisit Wajanasara
2. Hao Xu
