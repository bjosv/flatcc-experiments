# Issue with fallthrough and Boost

## Status:

https://github.com/dvidelabs/flatcc/issues/247

## Build

```
mkdir build && cd build
CXX=clang++ CC=clang cmake ..
make
```

## Issue

```
[ 94%] Building CXX object CMakeFiles/fallthrough.dir/main.cc.o
In file included from ..flatcc-experiments/issues/fallthrough/main.cc:5:
In file included from ..flatcc-experiments/issues/fallthrough/build/install/include/boost/lambda/lambda.hpp:14:
In file included from ..flatcc-experiments/issues/fallthrough/build/install/include/boost/lambda/core.hpp:25:
In file included from ..flatcc-experiments/issues/fallthrough/build/install/include/boost/config.hpp:39:
..flatcc-experiments/issues/fallthrough/build/install/include/boost/config/compiler/clang.hpp:315:26: error: missing ')' after '('
#if !__has_cpp_attribute(fallthrough) || __cplusplus < 201406L
                         ^~~~~~~~~~~
..flatcc-experiments/issues/fallthrough/build/install/include/flatcc/portable/pattributes.h:74:22: note: expanded from macro 'fallthrough'
# define fallthrough pattribute(fallthrough)
                     ^~~~~~~~~~~~~~~~~~~~~~~
..flatcc-experiments/issues/fallthrough/build/install/include/flatcc/portable/pattributes.h:69:23: note: expanded from macro 'pattribute'
#define pattribute(x) pattribute_##x
                      ^~~~~~~~~~~~~~
<scratch space>:281:1: note: expanded from here
pattribute_fallthrough
^~~~~~~~~~~~~~~~~~~~~~
..flatcc-experiments/issues/fallthrough/build/install/include/flatcc/portable/pattributes.h:63:46: note: expanded from macro 'pattribute_fallthrough'
# define pattribute_fallthrough __attribute__((__fallthrough__))
                                             ^
..flatcc-experiments/issues/fallthrough/build/install/include/boost/config/compiler/clang.hpp:315:25: note: to match this '('
#if !__has_cpp_attribute(fallthrough) || __cplusplus < 201406L
                        ^
1 error generated.
```
