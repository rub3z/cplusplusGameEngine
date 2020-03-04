#pragma once
// Window resolution.
const float RESOLUTION_X = 1920.0f;
const float RESOLUTION_Y = 1080.0f;

// Player attributes.
const float PLAYER_SPEED = 5.0f;

// Bullet / Projectile attributes.
const int   MAX_BULLETS = 200;
const float BULLET_SPEED = 10.0f;
const int   BULLET_SPREAD = 32;
const float BULLET_LIFETIME = 1.0f;
const int   SPREAD_BULLETS = 7;
const float RAPID_FIRE_RATE = 0.02f;
const float SPREAD_FIRE_RATE = 0.12f;

// Enemy attributes.
const int   MAX_ENEMY1 = 10;
const float ENEMY1_SPEED = 60.0f;
const float ENEMY1_ACCEL = 50.0f;
const float ENEMY1_RANDOM = 10.0f;

// Collision attributes.
const float AABB_FATNESS = 3.0f;

// Input.
const float INPUT_MAX = 100.0f;
const float INPUT_RESET = 0.0f;
const float INNER_DEADZONE = 25.0f;

// Keyboard.
static bool KEY_W, KEY_A, KEY_S, KEY_D, KEY_ESC;
static bool KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN;

// Gamepad inputs.
static bool BUTTON_RB_0, BUTTON_LB_0, BUTTON_B_0;
static float LSTICK_X_0, LSTICK_Y_0, RSTICK_X_0, RSTICK_Y_0;

static bool BUTTON_RB_1, BUTTON_LB_1, BUTTON_B_1;
static float LSTICK_X_1, LSTICK_Y_1, RSTICK_X_1, RSTICK_Y_1;

static bool BUTTON_RB_2, BUTTON_LB_2, BUTTON_B_2;
static float LSTICK_X_2, LSTICK_Y_2, RSTICK_X_2, RSTICK_Y_2;

static bool BUTTON_RB_3, BUTTON_LB_3, BUTTON_B_3;
static float LSTICK_X_3, LSTICK_Y_3, RSTICK_X_3, RSTICK_Y_3;
