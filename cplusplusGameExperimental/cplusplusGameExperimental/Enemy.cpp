#include "stdafx.h"
#include "Enemy.h"
#include "ConstantsNStuff.h"

Enemy::Enemy() {
   pTexture.loadFromFile("Player.png");
   pSprite.setTexture(pTexture);
   pSprite.setOrigin(5, 5);
   pSprite.setScale(15.0f, 15.0f);
   pSprite.setColor(Color(255, rand()%128, rand()%128, 255));

   enemyType = 0;

   pAccX = 0;
   pAccY = 0;

   pVelX = 0;
   pVelY = 0;

   pPosition.x = 0;
   pPosition.y = 0;
}

Enemy::Enemy(int type) {
   pTexture.loadFromFile("Player.png");
   pSprite.setTexture(pTexture);
   pSprite.setOrigin(5, 5);
   pSprite.setScale(1.5f, 1.5f);
   pSprite.setColor(Color(255, rand() % 128, rand() % 128, 255));

   enemyType = type;

   pAccX = 0;
   pAccY = 0;

   pVelX = 0;
   pVelY = 0;

   pPosition.x = 0;
   pPosition.y = 0;
}

Sprite& Enemy::getSprite() {
   return pSprite;
}

Vector2f& Enemy::getPosition() {
   return pPosition;
}

void Enemy::hit(FloatRect& other) {
   pPosition.x = 0;
   pPosition.y = 0;
}

void Enemy::hit()
{
   pPosition.x = 0;
   pPosition.y = 0;
}

void Enemy::update(float& elapsedTime, Vector2f& playerPos) {
   distanceX = playerPos.x - pPosition.x;
   distanceY = playerPos.y - pPosition.y;
   distance = sqrt(pow(distanceX, 2) + pow(distanceY, 2));
   pAccX = 0;
   pAccY = 0;
   switch (enemyType) {
   case 0:
      pVelX = (ENEMY1_SPEED / distance) * (distanceX) * elapsedTime + pAccX;
      pVelY = (ENEMY1_SPEED / distance) * (distanceY) * elapsedTime + pAccY;
      pPosition.x += pVelX;
      pPosition.y += pVelY;
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

      pPosition.x += pVelX;
      pPosition.y += pVelY;

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

      pPosition.x += pVelX + (((float)rand() / RAND_MAX) * ENEMY1_RANDOM) - (ENEMY1_RANDOM / 2);
      pPosition.y += pVelY + (((float)rand() / RAND_MAX) * ENEMY1_RANDOM) - (ENEMY1_RANDOM / 2);

      break;
   default:
      break;
   }

   pSprite.setPosition(pPosition);
}
