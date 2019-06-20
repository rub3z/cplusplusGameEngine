#include "stdafx.h"
#include "Enemy.h"
#include "ConstantsNStuff.h"

Enemy::Enemy() {
   pTexture.loadFromFile("Player.png");
   this->setTexture(pTexture);
   this->setOrigin(5, 5);
   this->setScale(15.0f, 15.0f);
   this->setColor(Color(255, rand()%128, rand()%128, 255));

   enemyType = 0;

   pAccX = 0;
   pAccY = 0;

   pVelX = 0;
   pVelY = 0;

   this->setPosition(0, 0);
   this->posX = 0;
   this->posY = 0;
}

Enemy::Enemy(int type) {
   pTexture.loadFromFile("Player.png");
   this->setTexture(pTexture);
   this->setOrigin(5, 5);
   this->setScale(1.5f, 1.5f);
   this->setColor(Color(255, rand() % 128, rand() % 128, 255));

   enemyType = type;

   pAccX = 0;
   pAccY = 0;

   pVelX = 0;
   pVelY = 0;

   this->setPosition(0, 0);
   this->posX = 0;
   this->posY = 0;
}

void Enemy::hit(FloatRect& other) {
   this->setPosition(0, 0);
}

void Enemy::hit()
{
   this->setPosition((((float)rand() / RAND_MAX) * 1920), 
                     (((float)rand() / RAND_MAX) * 1080));
}

void Enemy::update(float& elapsedTime, float& playerPosX, float& playerPosY) {
   distanceX = playerPosX - this->posX;
   distanceY = playerPosY - this->posY;
   distance = sqrt(pow(distanceX, 2) + pow(distanceY, 2));
   pAccX = 0;
   pAccY = 0;
   switch (enemyType) {
   case 0:
      pVelX = (ENEMY1_SPEED / distance) * (distanceX) * elapsedTime + pAccX;
      pVelY = (ENEMY1_SPEED / distance) * (distanceY) * elapsedTime + pAccY;
      this->move(pVelX, pVelY);
      this->posX += pVelX;
      this->posY += pVelY;
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
      this->move(pVelX, pVelY);
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

      this->move(pVelX + (((float)rand() / RAND_MAX) * ENEMY1_RANDOM) - (ENEMY1_RANDOM / 2),
                 pVelY + (((float)rand() / RAND_MAX) * ENEMY1_RANDOM) - (ENEMY1_RANDOM / 2));

      break;
   default:
      break;
   }
}
