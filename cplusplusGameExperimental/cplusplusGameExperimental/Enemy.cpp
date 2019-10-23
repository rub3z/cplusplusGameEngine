#include "stdafx.h"
#include "Enemy.h"

void hitEnemy1(ObjectInfo * o, ObjectInfo * that) {
   if (that->type < 2) {
      o->r = 0; o->g = 0; o->b = 0;
      o->posX = 0; o->posY = 0;
      o->collisionIndex = -1;
   }
}

Enemy::Enemy() {
   posX = 0;
   posY = 0;

   width = 100.0f;
   height = 100.0f;
   
   r = 255;
   enemyType = 0;
   
   pVelX = 0; pVelY = 0;
   pAccX = 0; pAccY = 0;

   distanceX = 0.0f; distanceY = 0.0f;
   distance = 0.0f;

   vT[0] = hitEnemy1;
   vTable = vT;

   type = 3;
}

Enemy::Enemy(int type) {
   enemyType = type;
   switch (enemyType) {
   case 0:
      posX = 0; posY = 0;
      width = 100.0f; height = 100.0f;
      r = 255;
      break;
   case 1:
      posX = 1800; posY = 0;
      width = 50.0f; height = 50.0f;
      b = 255;
      break;
   case 2:
      posX = 1900; posY = 1000;
      width = 25.0f; height = 25.0f;
      g = 128;
      b = 128;
      break;
   default:
      posX = 0; posY = 0;
      width = 100.0f; height = 100.0f;
      r = 255;
      enemyType = 0;
      break;
   }

   pVelX = 0; pVelY = 0;
   pAccX = 0; pAccY = 0;

   distanceX = 0.0f; distanceY = 0.0f;
   distance = 0.0f;

   vT[0] = hitEnemy1;
   vTable = vT;

   this->type = 3;
}

void Enemy::update(float& elapsedTime, float& playerPosX, float& playerPosY) {
   distanceX = playerPosX - posX;
   distanceY = playerPosY - posY;
   distance = sqrt(pow(distanceX, 2) + pow(distanceY, 2));
   pAccX = 0;
   pAccY = 0;
   switch (enemyType) {
   case 0:
      pVelX = (ENEMY1_SPEED / distance) * (distanceX) * elapsedTime + pAccX;
      pVelY = (ENEMY1_SPEED / distance) * (distanceY) * elapsedTime + pAccY;
      posX += pVelX;
      posY += pVelY;
      break;
   case 1:
      if (distance < 400) {
         pAccX = (ENEMY1_ACCEL / distance) * (distanceX) * elapsedTime;
         pAccY = (ENEMY1_ACCEL / distance) * (distanceY) * elapsedTime;
         pVelX += pAccX;
         pVelY += pAccY;
      }
      else {
         pVelX = (ENEMY1_SPEED / distance) * (distanceX) * elapsedTime + pAccX;
         pVelY = (ENEMY1_SPEED / distance) * (distanceY) * elapsedTime + pAccY;
      }
      posX += pVelX;
      posY += pVelY;

      break;
   case 2:
      if (distance < 400) {
         pAccX = (ENEMY1_ACCEL / distance) * (distanceX) * elapsedTime;
         pAccY = (ENEMY1_ACCEL / distance) * (distanceY) * elapsedTime;
         pVelX += pAccX;
         pVelY += pAccY;
      }
      else {
         pVelX = (ENEMY1_SPEED / distance) * (distanceX) * elapsedTime + pAccX;
         pVelY = (ENEMY1_SPEED / distance) * (distanceY) * elapsedTime + pAccY;
      }

      posX += pVelX + (((float)rand() / RAND_MAX) * ENEMY1_RANDOM) - (ENEMY1_RANDOM / 2);
      posY += pVelY + (((float)rand() / RAND_MAX) * ENEMY1_RANDOM) - (ENEMY1_RANDOM / 2);

      break;
   default:
      break;
   }
}

//void Enemy::hit() {
//   r = 0; g = 0; b = 0;
//   collisionIndex = -1;
//   std::cout << "guess I'll die now" << std::endl;
//}
