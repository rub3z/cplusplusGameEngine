#include "stdafx.h"
#include "Engine.h"

void Engine::input(float& dtAsSeconds) {
   // Fire rate updates.
   player0.fireRateDelta += dtAsSeconds;
   player1.fireRateDelta += dtAsSeconds;
   
   // Get the latest state of sf::Keyboard input.
   KEY_W = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
   KEY_A = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
   KEY_S = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
   KEY_D = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
   KEY_SPACE = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
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
      bullets.shoot(player0.centerX, player0.centerY,
           KEY_LEFT && !KEY_RIGHT ? -INPUT_MAX :
           !KEY_LEFT && KEY_RIGHT ? INPUT_MAX : 0.0f,
           KEY_UP && !KEY_DOWN ? -INPUT_MAX :
           !KEY_UP && KEY_DOWN ? INPUT_MAX : 0.0f,
             KEY_SPACE, player0.fireRateDelta);

   // Gamepad movement (which is obviously much better).
   if (sf::Joystick::isConnected(0)) {
      if (LSTICK_X_0 > INNER_DEADZONE || LSTICK_X_0 < -INNER_DEADZONE ||
          LSTICK_Y_0 > INNER_DEADZONE || LSTICK_Y_0 < -INNER_DEADZONE)
         player0.movement(LSTICK_X_0, LSTICK_Y_0);

      if (RSTICK_X_0 > INNER_DEADZONE || RSTICK_X_0 < -INNER_DEADZONE ||
          RSTICK_Y_0 > INNER_DEADZONE || RSTICK_Y_0 < -INNER_DEADZONE) {
         bullets.shoot(player0.centerX, player0.centerY,
            RSTICK_X_0, RSTICK_Y_0, BUTTON_RB_0, player0.fireRateDelta);
      }
   }

   if (sf::Joystick::isConnected(1)) {
      if (LSTICK_X_1 > INNER_DEADZONE || LSTICK_X_1 < -INNER_DEADZONE ||
          LSTICK_Y_1 > INNER_DEADZONE || LSTICK_Y_1 < -INNER_DEADZONE)
         player1.movement(LSTICK_X_1, LSTICK_Y_1);

      if (BUTTON_RB_1) {
         if (RSTICK_X_1 > 10 || RSTICK_X_1 < -10 ||
             RSTICK_Y_1 > 10 || RSTICK_Y_1 < -10) {
            bullets.shoot(player1.centerX, player1.centerY,
               RSTICK_X_1, RSTICK_Y_1, BUTTON_RB_1, player1.fireRateDelta);
         }
      }
   }

   sf::Joystick::update();
}
