# RadixMP

Parallel Radix Sort implementation using [OpenMP](http://www.openmp.org/), based on [this](https://haichuanwang.wordpress.com/2014/05/26/a-faster-openmp-radix-sort-implementation/) implementation with some minor tweaks, and with [CMake](https://cmake.org) as build system

### Instructions

```
git clone https://github.com/fogodev/radixmp.git
cd radixmp
cmake .
make
```

It will compile a static library to be linked at any executable
This library is compiled with -O3 optimization and will be in `./lib/`