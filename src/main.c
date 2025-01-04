#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define SCREEN_WIDTH GetScreenWidth()
#define SCREEN_HEIGHT GetScreenHeight()
#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720
#define MID_X (GetScreenWidth() / 2.0) - (WINDOW_WIDTH / 2.0)
#define MID_Y (GetScreenHeight() / 2.0) - (WINDOW_HEIGHT / 2.0)
#define FPS 60
#define MAX_ENTITIES 100

Vector2 POSITIONS[MAX_ENTITIES];
Vector2 VELOCITIES[MAX_ENTITIES];
bool VALID_ENTITIES[MAX_ENTITIES];
int objs_count = 0;

typedef int Enitiy_Id;
typedef enum { PLAYER, ENEMY } Enitiy;

typedef struct {
    Enitiy enitiy;
    Enitiy_Id id;
} Object;

void init_objects() {
    for (int i = 0; i < MAX_ENTITIES; i++) {
        POSITIONS[i] = (Vector2){0.0f, 0.0f};
        VELOCITIES[i] = (Vector2){0.0f, 0.0f};
        VALID_ENTITIES[i] = false;
    }
}

Enitiy_Id create_entity_id() {
    Enitiy_Id id = -1;
    for (Enitiy_Id i = 0; i < MAX_ENTITIES; i++) {
        if (!VALID_ENTITIES[i]) {
            id = i;
            break;
        }
    }
    return id;
}

Object create_obj(Enitiy enitiy, Vector2 pos, Vector2 vel) {
    Enitiy_Id id = create_entity_id();
    if (id == -1) {
        printf("Faild To Create Object");
        exit(1);
    }
    Object obj = (Object){.enitiy = enitiy, .id = id};

    POSITIONS[id] = pos;
    VELOCITIES[id] = vel;
    VALID_ENTITIES[id] = true;
    objs_count++;

    return obj;
}

void drop_obj(Object obj) {
    POSITIONS[obj.id].x = 0.0f;
    POSITIONS[obj.id].y = 0.0f;
    VELOCITIES[obj.id].x = 0.0f;
    VELOCITIES[obj.id].y = 0.0f;
    VALID_ENTITIES[obj.id] = false;
    objs_count--;
}

void load_obj_2d(Object obj, Texture2D texture) {
    DrawTextureEx(texture, POSITIONS[obj.id], 0.0f, 2.5f, WHITE);
}

void init_game() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "space invaders");
    SetWindowPosition(MID_X, MID_Y);
    SetTargetFPS(FPS);

    init_objects();
}

int main() {
    init_game();
    Object player_one = create_obj(
        PLAYER, (Vector2){GetScreenWidth() * 0.5, GetScreenHeight() * 0.9},
        (Vector2){100, 100});
    Image player_img = LoadImage("./assets/player.png");
    Texture2D player_texture = LoadTextureFromImage(player_img);
    UnloadImage(player_img);

    while (!WindowShouldClose()) {
        Vector2 direction = {0, 0};

        if (IsKeyDown(KEY_H))
            direction.x -= 1;
        if (IsKeyDown(KEY_L))
            direction.x += 1;
        if (IsKeyDown(KEY_J))
            direction.y += 1;
        if (IsKeyDown(KEY_K))
            direction.y -= 1;

        POSITIONS[player_one.id].x +=
            direction.x * VELOCITIES[player_one.id].x * GetFrameTime();
        POSITIONS[player_one.id].y +=
            direction.y * VELOCITIES[player_one.id].y * GetFrameTime();

        BeginDrawing();
        ClearBackground(BLACK);
        load_obj_2d(player_one, player_texture);
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
