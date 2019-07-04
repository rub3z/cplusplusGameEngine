#include "stdafx.h"
#include "Engine.h"

void Engine::draw(State & drawState)
{
   // Rub out the last frame
   m_Window.clear(Color::White);

   // Draw the background
   m_Window.draw(m_BackgroundSprite);

   // Draw sprites
   m_Window.draw(drawState);
   //m_Window.draw(playerAABB);
   //for (int i = 0; i < bulletAABBs.size(); i++) {
   //   m_Window.draw(bulletAABBs[i]);
   //}
   
   m_Window.display();
}