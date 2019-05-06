#include "stdafx.h"
#include "Enemies.h"
#include "stdafx.h"
#include "Enemies.h"

Enemies::Enemies()
{
   pTexture.loadFromFile("Player.png");
   baseSprite.setTexture(pTexture);
   baseSprite.setPosition(0, 0);
   baseSprite.setOrigin(5, 5);
   baseSprite.setScale(15.0f, 15.0f);
   baseSprite.setColor(Color(255, rand() % 128, rand() % 128, 255));

   this->assign(MAX_ENEMY1, baseSprite);
   enemyType = 0;

   pAccX = 0;
   pAccY = 0;

   vel.assign(MAX_ENEMY1, Vector2f(0, 0)); 
   for (int i = 0; i < MAX_ENEMY1; i++) {
      this->at(i).setPosition(i * 10.0f, 0.0f);
   }
}

Enemies::Enemies(int type)
{
   pTexture.loadFromFile("Player.png");
   baseSprite.setTexture(pTexture);
   baseSprite.setPosition(0, 0);
   baseSprite.setOrigin(5, 5);
   baseSprite.setColor(Color(255, rand() % 128, rand() % 128, 255));
   baseSprite.setScale(3, 3);
   
   this->assign(MAX_ENEMY1, baseSprite);
   
   enemyType = type;
   pAccX = 0;
   pAccY = 0;

   for (int i = 0; i < MAX_ENEMY1; i++)
   {
      velX[i] = 0; velY[i] = 0;
   }

   vel.assign(MAX_ENEMY1, Vector2f(0, 0));
   for (int i = 0; i < MAX_ENEMY1; i++) {
      this->at(i).setPosition(i * 10.0f, 0.0);
   }
}

void Enemies::collisionCheck(Sprite & other)
{
   for (int i = 0; i < MAX_ENEMY1; i++) {
      if (areColliding(this->at(i), other)) {
         this->at(i).setPosition((((float)rand() / RAND_MAX) * 1920),
                                 (((float)rand() / RAND_MAX) * 1080));
      }
   }
}

void Enemies::update(float & elapsedTime, const Vector2f & playerPos)
{
   // Credit to Tommy So for fixing this.
   for (int i = 0; i < MAX_ENEMY1; i++) {
      distanceX = playerPos.x - this->at(i).getPosition().x;
      distanceY = playerPos.y - this->at(i).getPosition().y;
      distance = sqrt(pow(distanceX, 2) + pow(distanceY, 2));
      pAccX = 0;
      pAccY = 0;
      switch (enemyType) {
      case 0:
         velX[i] = (ENEMY1_SPEED / distance) * (distanceX)* elapsedTime + pAccX;
         velY[i] = (ENEMY1_SPEED / distance) * (distanceY)* elapsedTime + pAccY;

         this->at(i).move(velX[i], velY[i]);
         break;
      case 1:
         if (distance < 400 ) {
            pAccX = (ENEMY1_ACCEL / distance) * (distanceX)* elapsedTime;
            pAccY = (ENEMY1_ACCEL / distance) * (distanceY)* elapsedTime;
            velX[i] += pAccX;
            velY[i] += pAccY;
         }
         else {
            velX[i] = (ENEMY1_SPEED / distance) * (distanceX)* elapsedTime + pAccX;
            velY[i] = (ENEMY1_SPEED / distance) * (distanceY)* elapsedTime + pAccY;
         }
         this->at(i).move(velX[i], velY[i]);

         break;
      case 2:
         if (distance < 400) {
            pAccX = (ENEMY1_ACCEL / distance) * (distanceX)* elapsedTime;
            pAccY = (ENEMY1_ACCEL / distance) * (distanceY)* elapsedTime;
            velX[i] += pAccX;
            velY[i] += pAccY;
         }
         else {
            velX[i] = (ENEMY1_SPEED / distance) * (distanceX)* elapsedTime + pAccX;
            velY[i] = (ENEMY1_SPEED / distance) * (distanceY)* elapsedTime + pAccY;
         }
         this->at(i).move(velX[i] + (((float)rand() / RAND_MAX) * ENEMY1_RANDOM) - (ENEMY1_RANDOM / 2),
            velY[i] + (((float)rand() / RAND_MAX) * ENEMY1_RANDOM) - (ENEMY1_RANDOM / 2));

         break;
      case 3:
         pAccX = (ENEMY1_ACCEL / distance) * (distanceX)* elapsedTime;
         pAccY = (ENEMY1_ACCEL / distance) * (distanceY)* elapsedTime;
         velX[i] += pAccX;
         velY[i] += pAccY;
         this->at(i).move(velX[i], velY[i]);
         break;
      case 4:
         pAccX = (ENEMY1_ACCEL / distance) * (distanceX)* elapsedTime;
         pAccY = (ENEMY1_ACCEL / distance) * (distanceY)* elapsedTime;
         velX[i] += pAccX;
         velY[i] += pAccY;
         this->at(i).move(velX[i] + (((float)rand() / RAND_MAX) * ENEMY1_RANDOM) - (ENEMY1_RANDOM / 2),
            velY[i] + (((float)rand() / RAND_MAX) * ENEMY1_RANDOM) - (ENEMY1_RANDOM / 2));
         break;
      default:
         break;
      }
   }
}
