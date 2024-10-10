#include <dlfcn.h>
#include <linux/limits.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static const int screenWidth = 800;
static const int screenHeight = 600;
static void *handle;
static void (*render_window)(int, int);

static char *get_path(void) {
    size_t cwd_size = PATH_MAX*sizeof(char);
    char *cwd = malloc(cwd_size);
    if (cwd == NULL) {
        fprintf(stderr, "Failed to allocate memory for PWD!\n");
        return NULL;
    }
    if (getcwd(cwd, cwd_size) == NULL) {
        fprintf(stderr, "Failed to get PWD\n");
        return NULL;
    }
    size_t cwd_len = strnlen(cwd, PATH_MAX);
    strncpy(cwd+cwd_len, "/libhot.so", 11);
    printf("%s\n", cwd);
    return cwd;
}

static bool get_func(void) {
    char *cwd = get_path();
    if (cwd == NULL) return false;

    handle = dlopen(cwd, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return false;
    }
    free(cwd);

    // clear errors
    dlerror();

    // workaround because casting a void * to a function pointer is undefined
    *(void **)(&render_window) = dlsym(handle, "render_window");

    char *err;
    if ((err = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", err);
        return false;
    }
    return true;
}

int main(void) {
    if (!get_func()) return 1;

    InitWindow(screenWidth, screenHeight, "hotreload");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_R)) {
            dlclose(handle);
            render_window = NULL;
            if (!get_func()) return 1;
        }

        BeginDrawing();
        render_window(screenWidth, screenHeight);
        EndDrawing();
    }

    CloseWindow();
    dlclose(handle);
    return 0;
}
