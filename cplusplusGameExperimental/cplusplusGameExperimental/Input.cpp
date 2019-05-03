#include "stdafx.h"
#include "Engine.h"

void Engine::input()
{
   // Get the latest state of keyboard input.
   KEY_W =   Keyboard::isKeyPressed(Keyboard::W);
   KEY_A =   Keyboard::isKeyPressed(Keyboard::A);
   KEY_S =   Keyboard::isKeyPressed(Keyboard::S);
   KEY_D =   Keyboard::isKeyPressed(Keyboard::D);
   KEY_ESC = Keyboard::isKeyPressed(Keyboard::Escape);

   // Get the latest state of gamepad input.
   LSTICK_X_0 =  Joystick::getAxisPosition(0, Joystick::X);
   LSTICK_Y_0 =  Joystick::getAxisPosition(0, Joystick::Y);
   RSTICK_X_0 =  Joystick::getAxisPosition(0, Joystick::U);
   RSTICK_Y_0 =  Joystick::getAxisPosition(0, Joystick::V);
   BUTTON_RB_0 = Joystick::isButtonPressed(0, 5);
   BUTTON_LB_0 = Joystick::isButtonPressed(0, 4);
   BUTTON_B_0 =  Joystick::isButtonPressed(0, 1);

   // Get the latest state of gamepad input.
   LSTICK_X_1 = Joystick::getAxisPosition(1, Joystick::X);
   LSTICK_Y_1 = Joystick::getAxisPosition(1, Joystick::Y);
   RSTICK_X_1 = Joystick::getAxisPosition(1, Joystick::U);
   RSTICK_Y_1 = Joystick::getAxisPosition(1, Joystick::V);
   BUTTON_RB_1 = Joystick::isButtonPressed(1, 5);
   BUTTON_LB_1 = Joystick::isButtonPressed(1, 4);
   BUTTON_B_1 = Joystick::isButtonPressed(1, 1);

   LSTICK_X_2 = Joystick::getAxisPosition(2, Joystick::X);
   LSTICK_Y_2 = Joystick::getAxisPosition(2, Joystick::Y);
   RSTICK_X_2 = Joystick::getAxisPosition(2, Joystick::U);
   RSTICK_Y_2 = Joystick::getAxisPosition(2, Joystick::V);
   BUTTON_RB_2 = Joystick::isButtonPressed(2, 5);
   BUTTON_LB_2 = Joystick::isButtonPressed(2, 4);
   BUTTON_B_2 = Joystick::isButtonPressed(2, 1);

   // Player can quit by pressing ESC or B button on pad.
   if (KEY_ESC || BUTTON_B_0) m_Window.close();

   // Keyboard movement.
   // Also, input into .move has to be reset to 0.
   // For some reason.
   player0.move(KEY_A && !KEY_D ? -INPUT_MAX :
                !KEY_A && KEY_D ? INPUT_MAX : 0.0f,
               KEY_W && !KEY_S ? -INPUT_MAX : 
                !KEY_W && KEY_S ? INPUT_MAX : 0.0f);
   player1.move(INPUT_RESET, INPUT_RESET);
   player2.move(INPUT_RESET, INPUT_RESET);

   // Gamepad movement (which is obviously much better).
   if (Joystick::isConnected(0)) {
      if (LSTICK_X_0 > INNER_DEADZONE || LSTICK_X_0 < -INNER_DEADZONE ||
          LSTICK_Y_0 > INNER_DEADZONE || LSTICK_Y_0 < -INNER_DEADZONE)
         player0.move(LSTICK_X_0, LSTICK_Y_0);

      // Rapid fire with RB.
      if (BUTTON_RB_0) {
         if (fireRateDeltaPlayer0 >= RAPID_FIRE_RATE) {
            if (RSTICK_X_0 > 10 || RSTICK_X_0 < -10 ||
               RSTICK_Y_0 > 10 || RSTICK_Y_0 < -10) {
               bullets[bulletCounter++].shootStraight(player0.getPosition(),
                  RSTICK_X_0, RSTICK_Y_0);
               if (bulletCounter >= MAX_BULLETS) bulletCounter = 0;
            }

            fireRateDeltaPlayer0 -= RAPID_FIRE_RATE;
         }
      }
      // Spread fire with LB.
      if (BUTTON_LB_0) {
         if (fireRateDeltaPlayer0 >= SPREAD_FIRE_RATE) {
            if (RSTICK_X_0 > 10 || RSTICK_X_0 < -10 ||
               RSTICK_Y_0 > 10 || RSTICK_Y_0 < -10) {
               for (spreadBulletCounter = 0;
                  spreadBulletCounter < SPREAD_BULLETS;
                  spreadBulletCounter++) {
                  bullets[bulletCounter++].shootSpread(player0.getPosition(),
                     RSTICK_X_0, RSTICK_Y_0);
                  if (bulletCounter >= MAX_BULLETS) bulletCounter = 0;
               }
            }
            fireRateDeltaPlayer0 -= SPREAD_FIRE_RATE;
         }
      }
   }

   if (Joystick::isConnected(1)) {
      if (LSTICK_X_1 > INNER_DEADZONE || LSTICK_X_1 < -INNER_DEADZONE ||
         LSTICK_Y_1 > INNER_DEADZONE || LSTICK_Y_1 < -INNER_DEADZONE)
         player1.move(LSTICK_X_1, LSTICK_Y_1);

      // Rapid fire with RB.
      if (BUTTON_RB_1) {
         if (fireRateDeltaPlayer1 >= RAPID_FIRE_RATE) {
            if (RSTICK_X_1 > 10 || RSTICK_X_1 < -10 ||
               RSTICK_Y_1 > 10 || RSTICK_Y_1 < -10) {
               bullets[bulletCounter++].shootStraight(player1.getPosition(),
                  RSTICK_X_1, RSTICK_Y_1);
               if (bulletCounter >= MAX_BULLETS) bulletCounter = 0;
            }
            fireRateDeltaPlayer1 = 0;
         }
      }

      if (BUTTON_LB_1) {
         if (fireRateDeltaPlayer1 >= SPREAD_FIRE_RATE) {
            if (RSTICK_X_1 > 10 || RSTICK_X_1 < -10 ||
               RSTICK_Y_1 > 10 || RSTICK_Y_1 < -10) {
               for (spreadBulletCounter = 0;
                  spreadBulletCounter < SPREAD_BULLETS;
                  spreadBulletCounter++) {
                  bullets[bulletCounter++].shootSpread(player1.getPosition(),
                     RSTICK_X_1, RSTICK_Y_1);
                  if (bulletCounter >= MAX_BULLETS) bulletCounter = 0;
               }
            }
            fireRateDeltaPlayer1 = 0;
         }
      }

   }

   if (Joystick::isConnected(2)) {
      if (LSTICK_X_2 > INNER_DEADZONE || LSTICK_X_2 < -INNER_DEADZONE ||
         LSTICK_Y_2 > INNER_DEADZONE || LSTICK_Y_2 < -INNER_DEADZONE)
         player2.move(LSTICK_X_2, LSTICK_Y_2);

      // Rapid fire with RB.
      if (BUTTON_RB_2) {
         if (fireRateDeltaPlayer2 >= RAPID_FIRE_RATE) {
            if (RSTICK_X_2 > 10 || RSTICK_X_2 < -10 ||
               RSTICK_Y_2 > 10 || RSTICK_Y_2 < -10) {
               bullets[bulletCounter++].shootStraight(player2.getPosition(),
                  RSTICK_X_2, RSTICK_Y_2);
               if (bulletCounter >= MAX_BULLETS) bulletCounter = 0;
            }
            fireRateDeltaPlayer2 = 0;
         }
      }

      if (BUTTON_LB_2) {
         if (fireRateDeltaPlayer2 >= SPREAD_FIRE_RATE) {
            if (RSTICK_X_2 > 10 || RSTICK_X_2 < -10 ||
               RSTICK_Y_2 > 10 || RSTICK_Y_2 < -10) {
               for (spreadBulletCounter = 0;
                  spreadBulletCounter < SPREAD_BULLETS;
                  spreadBulletCounter++) {
                  bullets[bulletCounter++].shootSpread(player2.getPosition(),
                     RSTICK_X_2, RSTICK_Y_2);
                  if (bulletCounter >= MAX_BULLETS) bulletCounter = 0;
               }
            }
            fireRateDeltaPlayer2 = 0;
         }
      }
   }

   Joystick::update();
}