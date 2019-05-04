#include "stdafx.h"
#include "Engine.h"

using namespace sf;

void Engine::update(float& dtAsSeconds)
{
   currentState.clear();
   player0.update(dtAsSeconds);
   currentState.add(player0);

   for (Projectile& p : bullets) {
      p.update(dtAsSeconds);
      currentState.add(p);
   }

   enemy.update(dtAsSeconds, player0.getPosition());
   if (areColliding(enemy, player0)) enemy.hit();
   currentState.add(enemy);

   for (Enemy& e : enemies) {
      e.update(dtAsSeconds, player0.getPosition());
      //if (areColliding(e, player0)) e.hit();
      currentState.add(e);
   }
}