#include "stdafx.h"
#include "Engine.h"

using namespace sf;

void Engine::update(float& dtAsSeconds)
{
   player0.update(dtAsSeconds);
   bullets.update(dtAsSeconds);
   enemy0.update(dtAsSeconds, player0.centerX, player0.centerY);
   enemy1.update(dtAsSeconds, player0.centerX, player0.centerY);
   enemy2.update(dtAsSeconds, player0.centerX, player0.centerY);
   enemies.update(dtAsSeconds, player0.centerX, player0.centerY);

   //aabbTree.update();

   static int aabbEnemy1 = 0;
   if (Keyboard::isKeyPressed(Keyboard::E)) {
      if (aabbEnemy1 == 0) {
         aabbTree.remove(enemy0.collisionIndex);
         aabbEnemy1 += 100;
      }
   }

   if (Keyboard::isKeyPressed(Keyboard::F)) {
      if (aabbEnemy1 == 100) {
         aabbTree.add(enemy0);
         aabbEnemy1 -= 100;
      }
   }

   static int aabbEnemy2 = 0;
   if (Keyboard::isKeyPressed(Keyboard::R)) {
      if (aabbEnemy2 == 0) {
         aabbTree.remove(enemy1.collisionIndex);
         aabbEnemy2 += 100;
      }
   }

   if (Keyboard::isKeyPressed(Keyboard::G)) {
      if (aabbEnemy2 == 100) {
         aabbTree.add(enemy1);
         aabbEnemy2 -= 100;
      }
   }


   static int aabbEnemy3 = 0;
   if (Keyboard::isKeyPressed(Keyboard::T)) {
      if (aabbEnemy3 == 0) {
         aabbTree.remove(enemy2.collisionIndex);
         aabbEnemy3 += 100;
      }
   }

   if (Keyboard::isKeyPressed(Keyboard::H)) {
      if (aabbEnemy3 == 100) {
         aabbTree.add(enemy2);
         aabbEnemy3 -= 100;
      }
   }

}