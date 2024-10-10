#include <raylib.h>

void render_window(int width, int height) {
    ClearBackground(RAYWHITE);
    DrawFPS(0, 0);
    DrawText("Hello, World!", width/2, height/2, 20, BLACK);
}
