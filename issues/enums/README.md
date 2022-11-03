# Issue with clang-tidy check: hicpp-signed-bitwise

## Status: FIXED

Fixed in `dc90c4358108b5829ee718f195034c896018108c`

## Build

```
mkdir build && cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
make
run-clang-tidy.py -checks='-*,hicpp-signed-bitwise' -p .
```

## Issue

```
/usr/bin/clang-tidy -checks=-*,hicpp-signed-bitwise -p=. .../issues/enums/main.c
.../issues/enums/main.c:27:43: warning: use of a signed integer operand with a binary bitwise operator [hicpp-signed-bitwise]
  flatcc_json_printer_set_flags(&printer, flatcc_json_printer_f_unquote |
                                          ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~
```
