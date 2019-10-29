#include "stdafx.h"
#include "Engine.h"

using namespace sf;

void Engine::update(float& dtAsSeconds)
{
   player0.update(dtAsSeconds);
   bullets.update(dtAsSeconds);
   //enemy0.update(dtAsSeconds, player0.centerX, player0.centerY);
   //enemy1.update(dtAsSeconds, player0.centerX, player0.centerY);
   //enemy2.update(dtAsSeconds, player0.centerX, player0.centerY);
   enemies.update(dtAsSeconds, player0.centerX, player0.centerY);

   for (GameObject * o : bullets.flagged) {
      aabbTree.add(*o);
   }
   for (GameObject * o : enemies.flagged) {
      aabbTree.add(*o);
   }
}