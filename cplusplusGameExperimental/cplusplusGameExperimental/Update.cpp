#include "stdafx.h"
#include "Engine.h"

using namespace sf;

void Engine::update(float& dtAsSeconds)
{
   player0.update(dtAsSeconds);
   bullets.update(dtAsSeconds);
   enemies.update(dtAsSeconds, player0.centerX, player0.centerY);
}