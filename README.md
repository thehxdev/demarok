# Demarok

Demarok is a file hider utility for unix systems inspired by [Amarok](https://github.com/deltazefiro/Amarok-Hider).
It's not fully compatible with original Amarok (I cloud not add `!amk` suffix to hidden file path name) but overal it's working.


## Build
To build Demarok you need `cmake`, a CXX compiler with `-std=gnu++17` support and a build program like gnu `make`.

```bash
# get the source code
git clone --depth=1 --branch=main https://github.com/thehxdev/demarok.git

cd demarok

mkdir -p build/

cmake -B build -S .

cmake --build build -- -j$(nproc)
```

## How to use
Here's the help message of demarok:
```bash
./build/demarok
# Usage: ./build/demarok <chmod/obfs> <hide/unhide> <file-path>
```
