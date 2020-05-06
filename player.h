#ifndef PLAYER_H221
#define PLAYER_H221

typedef int BOOL;

#ifndef TRUE
#define TRUE 1
#endif // TRUE

#ifndef FALSE
#define FALSE 0
#endif // FALSE

#include "view.h"

typedef struct
{
    BOOL forward;
    BOOL backward;
    BOOL left;
    BOOL right;
    BOOL run;
    BOOL crouch;
    BOOL jump;
} KeysPressed;

typedef struct
{
    float position[4];  // feet
    float velocity[4];
    float rotation[4];  // pitch, yaw, roll
    float width;
    float height;
    float speed;
    float sensitivity;
    float runFactor;
    float crouchFactor;
    float jumpSpeed;
    BOOL running;
    BOOL crouching;
    BOOL airborne;
    View view;
} Player;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void player_calcVelocity(Player* player, const KeysPressed* keysPressed);
void player_calcRotation(Player* player, int cursor_delta_x, int cursor_delta_y, float window_aspect);
void player_jump(Player* player);
void player_collision(Player* player);
void player_step(Player* player);

void player_loadProjection(const Player* player, float* mat4);
void player_loadView(const Player* player, float* mat4);
void player_multProjection(const Player* player, float* mat4);
void player_multView(const Player* player, float* mat4);

void player_viewWorld(const Player* player);
void player_viewWorld_center(const Player* player);
void player_viewWorld_feet(const Player* player);

float player_eyePos(const Player* player);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // PLAYER_H221