#include <raylib.h>

#define SCREEN_WIDTH GetScreenWidth()
#define SCREEN_HEIGHT GetScreenHeight()
#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720
#define MID_X (GetScreenWidth() / 2) - (WINDOW_WIDTH / 2)
#define MID_Y (GetScreenHeight() / 2) - (WINDOW_HEIGHT / 2)
#define FPS 60

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "space invaders");
    SetWindowPosition(MID_X, MID_Y);
	SetTargetFps(FPS);

    while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		EndDrawing();
    }

	CloseWindow();
    return 0;
}
