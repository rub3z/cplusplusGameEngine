#include "stdafx.h"
#include "Engine.h"

void Engine::input()
{
   // Handle the player quitting
   if (Keyboard::isKeyPressed(Keyboard::Escape))
   {
      m_Window.close();
   }

   if (Joystick::isButtonPressed(0, 1)) {
      m_Window.close(); 
   }

   // Handle the player moving
   player.moveX(Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D) ? -100 
      : !Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::D) ? 100 : 0);
   player.moveY(Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::S) ? -100
      : !Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::S) ? 100 : 0);

   if (Joystick::isConnected(0)) {
      player.moveX(Joystick::getAxisPosition(0, Joystick::X));
      player.moveY(Joystick::getAxisPosition(0, Joystick::Y));
   }
   Joystick::update();
}