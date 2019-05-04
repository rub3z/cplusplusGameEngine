#include "stdafx.h"
#include "Engine.h"

void Engine::draw(State & drawState)
{
   // Rub out the last frame
   m_Window.clear(Color::White);

   // Draw the background
   m_Window.draw(m_BackgroundSprite);
   m_Window.draw(drawState);

   m_Window.display();
}