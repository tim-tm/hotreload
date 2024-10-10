#!/bin/sh

set -xe

# build lib
gcc -fPIC -Wall -Wextra -c render.c -o render.o
gcc -Wall -Wextra render.o -shared -o libhot.so -lraylib

# build main
gcc -Wall -Wextra -pedantic main.c -o app -lraylib
