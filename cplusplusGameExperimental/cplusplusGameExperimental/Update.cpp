#include "stdafx.h"
#include "Engine.h"

using namespace sf;

void Engine::update(float& dtAsSeconds)
{

   player0.update(dtAsSeconds);

   for (Projectile& p : bullets) {
      p.update(dtAsSeconds);
   }

   enemies.update(dtAsSeconds, player0.getPosition());
   enemies.collisionCheck(player0);
}