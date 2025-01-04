#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH GetScreenWidth()
#define SCREEN_HEIGHT GetScreenHeight()
#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720
#define MID_X (GetScreenWidth() / 2.0) - (WINDOW_WIDTH / 2.0)
#define MID_Y (GetScreenHeight() / 2.0) - (WINDOW_HEIGHT / 2.0)
#define FPS 60
#define MAX_OBJECTS 100

Vector2 POSITIONS[MAX_OBJECTS];
Vector2 VELOCITIES[MAX_OBJECTS];
bool VALID_OBJ[MAX_OBJECTS];
int objs_count = 0;

typedef int Enitiy_Id;

typedef enum { PLAYER, ENEMY } Enitiy;
typedef struct {
    Enitiy type;
    Enitiy_Id id;
} Object;

void init_objects() {
    for (int i = 0; i < MAX_OBJECTS; i++) {
        POSITIONS[i] = (Vector2){0.0f, 0.0f};
        VELOCITIES[i] = (Vector2){0.0f, 0.0f};
        VALID_OBJ[i] = false;
    }
}

Enitiy_Id create_entity_id() {
    Enitiy_Id id = -1;
    for (Enitiy_Id i = 0; i < MAX_OBJECTS; i++) {
        if (!VALID_OBJ[i]) {
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
    Object obj = (Object){.type = enitiy, .id = id};

    POSITIONS[id] = pos;
    VELOCITIES[id] = vel;
    VALID_OBJ[id] = true;
    objs_count++;

    return obj;
}

void drop_obj(Object obj) {
    POSITIONS[obj.id].x = 0.0f;
    POSITIONS[obj.id].y = 0.0f;
    VELOCITIES[obj.id].x = 0.0f;
    VELOCITIES[obj.id].y = 0.0f;
    VALID_OBJ[obj.id] = false;
    objs_count--;
}

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "space invaders");
    SetWindowPosition(MID_X, MID_Y);
    SetTargetFPS(FPS);

    init_objects();
    Object player_one =
        create_obj(PLAYER, (Vector2){MID_X, MID_Y}, (Vector2){0, 0});

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle(POSITIONS[player_one.id].x, POSITIONS[player_one.id].y,
                      50, 50, BLUE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
