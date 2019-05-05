#include "stdafx.h"
#include "Engine.h"

using namespace sf;

void Engine::update(float& dtAsSeconds)
{

   player0.update(dtAsSeconds);

   for (Projectile& p : bullets) {
      p.update(dtAsSeconds);
   }

   enemy.update(dtAsSeconds, player0.getPosition());
   if (areColliding(enemy, player0)) enemy.hit();
   
   for (Enemy& e : enemies) {
      e.update(dtAsSeconds, player0.getPosition());
      if (areColliding(e, player0)) e.hit();
   }
}