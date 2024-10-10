# hotreload

Hotreload is a simple project that may be used as a base for writing hot-reloadable applications in C using [raylib](https://github.com/raysan5/raylib).

The file `render.c` will be compiled into `libhot.so`, `main.c` will load `libhot.so` dynamically and reload if needed.
