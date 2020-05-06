#include "player.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include "mglm.h"
#include "vec.h"
#include "frustum.h"

static const float F_g = -9.80665f / 60.0f / 10.0f; // / 3.0f

void player_calcVelocity(Player* player, const KeysPressed* keysPressed)
{
    float velocity_view[2];
    float velocity_world[2];
    
    int x_view = keysPressed->right - keysPressed->left;
    int z_view = keysPressed->backward - keysPressed->forward;

    // update state
    player->running = keysPressed->run;
    player->crouching = keysPressed->crouch;

    // if any keys are pressed at all
    if (x_view || z_view)
    {
        velocity_view[0] = (float)x_view * player->speed;
        velocity_view[1] = (float)z_view * player->speed;

        // normalize quickly
        if (x_view && z_view)
        {
            velocity_view[0] *= (float)M_SQRT1_2;
            velocity_view[1] *= (float)M_SQRT1_2;
        }

        // crouching takes priority over running
        if (player->crouching)
        {
            velocity_view[0] *= player->crouchFactor;
            velocity_view[1] *= player->crouchFactor;
        }
        else if (player->running)
        {
            velocity_view[0] *= player->runFactor;
            velocity_view[1] *= player->runFactor;
        }

        // view-space to world-space
        vec2_rotate_dst(velocity_world, velocity_view, -player->rotation[1]);

        player->velocity[0] = velocity_world[0];
        player->velocity[2] = velocity_world[1];
    }
    else
    {
        player->velocity[0] = 0.0f;
        player->velocity[2] = 0.0f;
    }
}

void player_calcRotation(Player* player, int cursor_delta_x, int cursor_delta_y, float window_aspect)
{
    // inc rotation proportional to difference from center
    player->rotation[0] += player->sensitivity / -10.0f * (float)(cursor_delta_y);
    player->rotation[1] += player->sensitivity / -10.0f * (float)(cursor_delta_x) * window_aspect;
}

void player_jump(Player* player)
{
    if (!player->airborne)
    {
        player->airborne = TRUE;

        player->velocity[1] = player->jumpSpeed;
    }
}

void player_collision(Player* player)
{
    // simple for now
    if (player->airborne &&
        player->velocity[1] < 0.0f &&
        player->position[1] <= 0.0f)
    {
        player->airborne = FALSE;
    }
}

void player_step(Player* player)
{
    if (player->airborne)
    {
        player->velocity[1] += F_g;
    }
    else
    {
        player->velocity[1] = 0.0f;
    }
    
    vec3_addv(player->position, player->velocity);
}

void player_loadProjection(const Player* player, float* mat4)
{
    mglmLoadPerspective(mat4, player->view.fov, player->view.aspect, player->view.zNear, player->view.zFar);
}

void player_loadView(const Player* player, float* mat4)
{
    mglmLoadIdentity(mat4);
    player_multView(player, mat4);
}

void player_multProjection(const Player* player, float* mat4)
{
    mglmPerspective(mat4, player->view.fov, player->view.aspect, player->view.zNear, player->view.zFar);
}

void player_multView(const Player* player, float* mat4)
{
    mglmRotateX(mat4, -player->rotation[0]);
    mglmRotateY(mat4, -player->rotation[1]);
    mglmRotateZ(mat4, -player->rotation[2]);
    mglmTranslate(mat4, -player->position[0],
                        -player->position[1] - player_eyePos(player),
                        -player->position[2]);
}

// ACCESSORS

float player_eyePos(const Player* player)
{
    /*
     * baby = 4 heads tall
     * child = 5 heads tall
     * youth = 6 heads tall
     * teen = 7 heads tall
     * adult = 8 heads tall
     */

    /*
     * eyes are in the center
     * of the head
     */

    float standing = player->height * 15.0f / 16.0f;

    return player->crouching ? standing * 0.6f : standing;
}