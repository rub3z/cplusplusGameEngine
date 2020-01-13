#include "stdafx.h"
#include "Engine.h"

void Engine::input(float& dtAsSeconds) {
   // Fire rate updates.
   fireRateDeltaPlayer0 += dtAsSeconds;
   fireRateDeltaPlayer1 += dtAsSeconds;

   // Get the latest state of sf::Keyboard input.
   KEY_W = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
   KEY_A = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
   KEY_S = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
   KEY_D = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
   KEY_LEFT  = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
   KEY_DOWN  = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
   KEY_RIGHT = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
   KEY_UP    = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);

   KEY_ESC = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

   // Get the latest state of gamepad input.
   LSTICK_X_0 = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
   LSTICK_Y_0 = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
   RSTICK_X_0 = sf::Joystick::getAxisPosition(0, sf::Joystick::U);
   RSTICK_Y_0 = sf::Joystick::getAxisPosition(0, sf::Joystick::V);
   BUTTON_RB_0 = sf::Joystick::isButtonPressed(0, 5);
   BUTTON_LB_0 = sf::Joystick::isButtonPressed(0, 4);
   BUTTON_B_0 = sf::Joystick::isButtonPressed(0, 1);

   // Get the latest state of gamepad input.
   LSTICK_X_1 = sf::Joystick::getAxisPosition(1, sf::Joystick::X);
   LSTICK_Y_1 = sf::Joystick::getAxisPosition(1, sf::Joystick::Y);
   RSTICK_X_1 = sf::Joystick::getAxisPosition(1, sf::Joystick::U);
   RSTICK_Y_1 = sf::Joystick::getAxisPosition(1, sf::Joystick::V);
   BUTTON_RB_1 = sf::Joystick::isButtonPressed(1, 5);
   BUTTON_LB_1 = sf::Joystick::isButtonPressed(1, 4);
   BUTTON_B_1 = sf::Joystick::isButtonPressed(1, 1);


   // Player can quit by pressing ESC or B button on pad.
   if (KEY_ESC || BUTTON_B_0) m_Window.close();

   // Keyboard movement.
   // Also, input into .movement has to be reset to 0.
   // For some reason.
   player0.movement(
      KEY_A && !KEY_D ? -INPUT_MAX :
      !KEY_A && KEY_D ? INPUT_MAX : 0.0f,
      KEY_W && !KEY_S ? -INPUT_MAX :
      !KEY_W && KEY_S ? INPUT_MAX : 0.0f);
   player1.movement(0.0f, 0.0f);

   // Keyboard shooting with arrow keys.
   if (KEY_UP || KEY_DOWN || KEY_LEFT || KEY_RIGHT)
      if (fireRateDeltaPlayer0 >= RAPID_FIRE_RATE) {
         fireRateDeltaPlayer0 = RAPID_FIRE_RATE;
          bullets.shootStraight(player0.centerX, player0.centerY,
           KEY_LEFT && !KEY_RIGHT ? -INPUT_MAX :
           !KEY_LEFT && KEY_RIGHT ? INPUT_MAX : 0.0f,
           KEY_UP && !KEY_DOWN ? -INPUT_MAX :
           !KEY_UP && KEY_DOWN ? INPUT_MAX : 0.0f);
         fireRateDeltaPlayer0 -= RAPID_FIRE_RATE;
   }
   // Gamepad movement (which is obviously much better).
   if (sf::Joystick::isConnected(0)) {
      if (LSTICK_X_0 > INNER_DEADZONE || LSTICK_X_0 < -INNER_DEADZONE ||
         LSTICK_Y_0 > INNER_DEADZONE || LSTICK_Y_0 < -INNER_DEADZONE)
         player0.movement(LSTICK_X_0, LSTICK_Y_0);

      // Rapid fire with RB.
      // Credit to Tommy So for fixing this.
      if (BUTTON_RB_0) {
         if (fireRateDeltaPlayer0 >= RAPID_FIRE_RATE) {
            fireRateDeltaPlayer0 = RAPID_FIRE_RATE;
            if (RSTICK_X_0 > 10 || RSTICK_X_0 < -10 ||
               RSTICK_Y_0 > 10 || RSTICK_Y_0 < -10) {
                bullets.shootStraight(player0.centerX, player0.centerY,
                 RSTICK_X_0, RSTICK_Y_0);
               fireRateDeltaPlayer0 -= RAPID_FIRE_RATE;
            }
         }
      }
      // Spread fire with LB.
      // Credit to Tommy So for fixing this.
      if (BUTTON_LB_0) {
         if (fireRateDeltaPlayer0 >= SPREAD_FIRE_RATE) {
            fireRateDeltaPlayer0 = SPREAD_FIRE_RATE;
            if (RSTICK_X_0 > 10 || RSTICK_X_0 < -10 ||
               RSTICK_Y_0 > 10 || RSTICK_Y_0 < -10) {
               for (int i = 0; i < SPREAD_BULLETS; i++) {
                  bullets.shootSpread(player0.centerX, player0.centerY,
                    RSTICK_X_0, RSTICK_Y_0);
               }
               fireRateDeltaPlayer0 -= SPREAD_FIRE_RATE;
            }
         }
      }
   }

   if (sf::Joystick::isConnected(1)) {
      if (LSTICK_X_1 > INNER_DEADZONE || LSTICK_X_1 < -INNER_DEADZONE ||
         LSTICK_Y_1 > INNER_DEADZONE || LSTICK_Y_1 < -INNER_DEADZONE)
         player1.movement(LSTICK_X_1, LSTICK_Y_1);

      // Rapid fire with RB.
      // Credit to Tommy So for fixing this.
      if (BUTTON_RB_1) {
         if (fireRateDeltaPlayer1 >= RAPID_FIRE_RATE) {
            fireRateDeltaPlayer1 = RAPID_FIRE_RATE;
            if (RSTICK_X_1 > 10 || RSTICK_X_1 < -10 ||
               RSTICK_Y_1 > 10 || RSTICK_Y_1 < -10) {
               bullets.shootStraight(player1.centerX, player1.centerY,
                  RSTICK_X_1, RSTICK_Y_1);
               fireRateDeltaPlayer1 -= RAPID_FIRE_RATE;
            }
         }
      }
      // Spread fire with LB.
      // Credit to Tommy So for fixing this.
      if (BUTTON_LB_1) {
         if (fireRateDeltaPlayer1 >= SPREAD_FIRE_RATE) {
            fireRateDeltaPlayer1 = SPREAD_FIRE_RATE;
            if (RSTICK_X_1 > 10 || RSTICK_X_1 < -10 ||
               RSTICK_Y_1 > 10 || RSTICK_Y_1 < -10) {
               for (int i = 0; i < SPREAD_BULLETS; i++) {
                  bullets.shootSpread(player1.centerX, player1.centerY,
                     RSTICK_X_1, RSTICK_Y_1);
               }
               fireRateDeltaPlayer1 -= SPREAD_FIRE_RATE;
            }
         }
      }
   }

   sf::Joystick::update();
}

void Engine::input()
{
   //// Get the latest state of Keyboard input.
   //KEY_W =   sf::Keyboard::isKeyPressed(sf::Keyboard::W);
   //KEY_A =   sf::Keyboard::isKeyPressed(sf::Keyboard::A);
   //KEY_S =   sf::Keyboard::isKeyPressed(sf::Keyboard::S);
   //KEY_D =   sf::Keyboard::isKeyPressed(sf::Keyboard::D);
   //KEY_ESC = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

   //// Get the latest state of gamepad input.
   //LSTICK_X_0 =  sf::Joystick::getAxisPosition(0, sf::Joystick::X);
   //LSTICK_Y_0 =  sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
   //RSTICK_X_0 =  sf::Joystick::getAxisPosition(0, sf::Joystick::U);
   //RSTICK_Y_0 =  sf::Joystick::getAxisPosition(0, sf::Joystick::V);
   //BUTTON_RB_0 = sf::Joystick::isButtonPressed(0, 5);
   //BUTTON_LB_0 = sf::Joystick::isButtonPressed(0, 4);
   //BUTTON_B_0 =  sf::Joystick::isButtonPressed(0, 1);

   //// Get the latest state of gamepad input.
   //LSTICK_X_1 = sf::Joystick::getAxisPosition(1, sf::Joystick::X);
   //LSTICK_Y_1 = sf::Joystick::getAxisPosition(1, sf::Joystick::Y);
   //RSTICK_X_1 = sf::Joystick::getAxisPosition(1, sf::Joystick::U);
   //RSTICK_Y_1 = sf::Joystick::getAxisPosition(1, sf::Joystick::V);
   //BUTTON_RB_1 = sf::Joystick::isButtonPressed(1, 5);
   //BUTTON_LB_1 = sf::Joystick::isButtonPressed(1, 4);
   //BUTTON_B_1 = sf::Joystick::isButtonPressed(1, 1);

   //LSTICK_X_2 = sf::Joystick::getAxisPosition(2, sf::Joystick::X);
   //LSTICK_Y_2 = sf::Joystick::getAxisPosition(2, sf::Joystick::Y);
   //RSTICK_X_2 = sf::Joystick::getAxisPosition(2, sf::Joystick::U);
   //RSTICK_Y_2 = sf::Joystick::getAxisPosition(2, sf::Joystick::V);
   //BUTTON_RB_2 = sf::Joystick::isButtonPressed(2, 5);
   //BUTTON_LB_2 = sf::Joystick::isButtonPressed(2, 4);
   //BUTTON_B_2 = sf::Joystick::isButtonPressed(2, 1);

   //// Player can quit by pressing ESC or B button on pad.
   //if (KEY_ESC || BUTTON_B_0) m_Window.close();

   //// Keyboard movement.
   //// Also, input into .movement has to be reset to 0.
   //// For some reason.
   //player0.movement(KEY_A && !KEY_D ? -INPUT_MAX :
   //             !KEY_A && KEY_D ? INPUT_MAX : 0.0f,
   //            KEY_W && !KEY_S ? -INPUT_MAX : 
   //             !KEY_W && KEY_S ? INPUT_MAX : 0.0f);
   //player1.movement(INPUT_RESET, INPUT_RESET);
   //player2.movement(INPUT_RESET, INPUT_RESET);

   //// Gamepad movement (which is obviously much better).
   //if (sf::Joystick::isConnected(0)) {
   //   if (LSTICK_X_0 > INNER_DEADZONE || LSTICK_X_0 < -INNER_DEADZONE ||
   //       LSTICK_Y_0 > INNER_DEADZONE || LSTICK_Y_0 < -INNER_DEADZONE)
   //      player0.movement(LSTICK_X_0, LSTICK_Y_0);

   //   // Rapid fire with RB.
   //   if (BUTTON_RB_0) {
   //      if (fireRateDeltaPlayer0 >= RAPID_FIRE_RATE) {
   //         if (RSTICK_X_0 > 10 || RSTICK_X_0 < -10 ||
   //            RSTICK_Y_0 > 10 || RSTICK_Y_0 < -10) {
   //            bullets[bulletCounter++].shootStraight(player0.getPosition(),
   //               RSTICK_X_0, RSTICK_Y_0);
   //            if (bulletCounter >= MAX_BULLETS) bulletCounter = 0;
   //         }

   //         fireRateDeltaPlayer0 -= RAPID_FIRE_RATE;
   //      }
   //   }
   //   // Spread fire with LB.
   //   if (BUTTON_LB_0) {
   //      if (fireRateDeltaPlayer0 >= SPREAD_FIRE_RATE) {
   //         if (RSTICK_X_0 > 10 || RSTICK_X_0 < -10 ||
   //            RSTICK_Y_0 > 10 || RSTICK_Y_0 < -10) {
   //            for (spreadBulletCounter = 0;
   //               spreadBulletCounter < SPREAD_BULLETS;
   //               spreadBulletCounter++) {
   //               bullets[bulletCounter++].shootSpread(player0.getPosition(),
   //                  RSTICK_X_0, RSTICK_Y_0);
   //               if (bulletCounter >= MAX_BULLETS) bulletCounter = 0;
   //            }
   //         }
   //         fireRateDeltaPlayer0 -= SPREAD_FIRE_RATE;
   //      }
   //   }
   //}

   //if (sf::Joystick::isConnected(1)) {
   //   if (LSTICK_X_1 > INNER_DEADZONE || LSTICK_X_1 < -INNER_DEADZONE ||
   //      LSTICK_Y_1 > INNER_DEADZONE || LSTICK_Y_1 < -INNER_DEADZONE)
   //      player1.movement(LSTICK_X_1, LSTICK_Y_1);

   //   // Rapid fire with RB.
   //   if (BUTTON_RB_1) {
   //      if (fireRateDeltaPlayer1 >= RAPID_FIRE_RATE) {
   //         if (RSTICK_X_1 > 10 || RSTICK_X_1 < -10 ||
   //            RSTICK_Y_1 > 10 || RSTICK_Y_1 < -10) {
   //            bullets[bulletCounter++].shootStraight(player1.getPosition(),
   //               RSTICK_X_1, RSTICK_Y_1);
   //            if (bulletCounter >= MAX_BULLETS) bulletCounter = 0;
   //         }
   //         fireRateDeltaPlayer1 = 0;
   //      }
   //   }

   //   if (BUTTON_LB_1) {
   //      if (fireRateDeltaPlayer1 >= SPREAD_FIRE_RATE) {
   //         if (RSTICK_X_1 > 10 || RSTICK_X_1 < -10 ||
   //            RSTICK_Y_1 > 10 || RSTICK_Y_1 < -10) {
   //            for (spreadBulletCounter = 0;
   //               spreadBulletCounter < SPREAD_BULLETS;
   //               spreadBulletCounter++) {
   //               bullets[bulletCounter++].shootSpread(player1.getPosition(),
   //                  RSTICK_X_1, RSTICK_Y_1);
   //               if (bulletCounter >= MAX_BULLETS) bulletCounter = 0;
   //            }
   //         }
   //         fireRateDeltaPlayer1 = 0;
   //      }
   //   }

   //}

   //if (sf::Joystick::isConnected(2)) {
   //   if (LSTICK_X_2 > INNER_DEADZONE || LSTICK_X_2 < -INNER_DEADZONE ||
   //      LSTICK_Y_2 > INNER_DEADZONE || LSTICK_Y_2 < -INNER_DEADZONE)
   //      player2.movement(LSTICK_X_2, LSTICK_Y_2);

   //   // Rapid fire with RB.
   //   if (BUTTON_RB_2) {
   //      if (fireRateDeltaPlayer2 >= RAPID_FIRE_RATE) {
   //         if (RSTICK_X_2 > 10 || RSTICK_X_2 < -10 ||
   //            RSTICK_Y_2 > 10 || RSTICK_Y_2 < -10) {
   //            bullets[bulletCounter++].shootStraight(player2.getPosition(),
   //               RSTICK_X_2, RSTICK_Y_2);
   //            if (bulletCounter >= MAX_BULLETS) bulletCounter = 0;
   //         }
   //         fireRateDeltaPlayer2 = 0;
   //      }
   //   }

   //   if (BUTTON_LB_2) {
   //      if (fireRateDeltaPlayer2 >= SPREAD_FIRE_RATE) {
   //         if (RSTICK_X_2 > 10 || RSTICK_X_2 < -10 ||
   //            RSTICK_Y_2 > 10 || RSTICK_Y_2 < -10) {
   //            for (spreadBulletCounter = 0;
   //               spreadBulletCounter < SPREAD_BULLETS;
   //               spreadBulletCounter++) {
   //               bullets[bulletCounter++].shootSpread(player2.getPosition(),
   //                  RSTICK_X_2, RSTICK_Y_2);
   //               if (bulletCounter >= MAX_BULLETS) bulletCounter = 0;
   //            }
   //         }
   //         fireRateDeltaPlayer2 = 0;
   //      }
   //   }
   //}

   //sf::Joystick::update();
}