#include "stdafx.h"
#include "Engine.h"

using namespace sf;

void Engine::update(float& dtAsSeconds)
{
   player0.update(dtAsSeconds);
   enemy.update(dtAsSeconds, player0.posX, player0.posY);
   bullets.update(dtAsSeconds);
   enemies.update(dtAsSeconds, player0.posX, player0.posY);
   //enemies.collisionCheck(player0);
}