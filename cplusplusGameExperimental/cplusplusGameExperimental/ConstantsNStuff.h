#pragma once
const float PLAYER_SPEED = 10;

const int   MAX_BULLETS = 200;
const float BULLET_SPEED = 10;
const int   BULLET_SPREAD = 24;
const float BULLET_LIFETIME = 2.0f;

const float INNER_DEADZONE = 25;
const float INPUT_MAX = 100;
const float RAPID_FIRE_RATE = 0.05f;
const float SPREAD_FIRE_RATE = 0.15f;
const int   SPREAD_BULLETS = 15;

const int MAX_ENEMY1 = 2000;
const float ENEMY1_SPEED = 600;
const float ENEMY1_ACCEL = 50.0f;
const float ENEMY1_RANDOM = 10;


const float INPUT_RESET = 0;
static bool KEY_W, KEY_A, KEY_S, KEY_D, KEY_ESC;
static bool BUTTON_RB_0, BUTTON_LB_0, BUTTON_B_0;
static float LSTICK_X_0, LSTICK_Y_0, RSTICK_X_0, RSTICK_Y_0;

static bool BUTTON_RB_1, BUTTON_LB_1, BUTTON_B_1;
static float LSTICK_X_1, LSTICK_Y_1, RSTICK_X_1, RSTICK_Y_1;

static bool BUTTON_RB_2, BUTTON_LB_2, BUTTON_B_2;
static float LSTICK_X_2, LSTICK_Y_2, RSTICK_X_2, RSTICK_Y_2;

static bool BUTTON_RB_3, BUTTON_LB_3, BUTTON_B_3;
static float LSTICK_X_3, LSTICK_Y_3, RSTICK_X_3, RSTICK_Y_3;
