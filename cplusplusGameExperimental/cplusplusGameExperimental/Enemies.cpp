#include "stdafx.h"
#include "Enemies.h"
#include "stdafx.h"
#include "Enemies.h"
#include "ConstantsNStuff.h"

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

   pVelX = 0;
   pVelY = 0;
}

Enemies::Enemies(int type)
{
   pTexture.loadFromFile("Player.png");
   baseSprite.setTexture(pTexture);
   baseSprite.setPosition(0, 0);
   baseSprite.setOrigin(5, 5);
   baseSprite.setColor(Color(255, rand() % 128, rand() % 128, 255));
   baseSprite.setScale(1.5f, 1.5f);
   
   this->assign(MAX_ENEMY1, baseSprite);
   
   enemyType = type;
   pAccX = 0;
   pAccY = 0;

   pVelX = 0;
   pVelY = 0;
   for (int i = 0; i < MAX_ENEMY1; i++) {
      if (i < 10)      this->at(i).setPosition(i * 100, 0);
      else if (i < 20) this->at(i).setPosition((i - 10) * 100, 100);
      else if (i < 30) this->at(i).setPosition((i - 20) * 100, 200);
      else if (i < 40) this->at(i).setPosition((i - 30) * 100, 300);
      else if (i < 50) this->at(i).setPosition((i - 40) * 100, 400);

   }
}

void Enemies::hit(FloatRect & other)
{
}

void Enemies::hit()
{
}

void Enemies::update(float & elapsedTime, const Vector2f & playerPos)
{
   distance = 0;
   //distanceX = 0;
   //distanceY = 0;
   //pAccX = 0;
   //pAccY = 0;
   //pVelX = 0;
   //pVelY = 0;
   for (int i = 0; i < MAX_ENEMY1; i++) {
      distanceX = playerPos.x - this->at(i).getPosition().x;
      distanceY = playerPos.y - this->at(i).getPosition().y;
      distance = sqrt(pow(distanceX, 2) + pow(distanceY, 2));
      //pAccX = 0;
      //pAccY = 0;
      //pVelX = 0;
      //pVelY = 0;
      switch (enemyType) {
      case 0:
         pVelX = (ENEMY1_SPEED / distance) * (distanceX)* elapsedTime + pAccX;
         pVelY = (ENEMY1_SPEED / distance) * (distanceY)* elapsedTime + pAccY;
         this->at(i).move(pVelX, pVelY);
         break;
      case 1:
         if (distance < 400) {
            pAccX = (ENEMY1_ACCEL / distance) * (distanceX)* elapsedTime;
            pAccY = (ENEMY1_ACCEL / distance) * (distanceY)* elapsedTime;
            pVelX += pAccX;
            pVelY += pAccY;
         }
         else {
            pVelX = (ENEMY1_SPEED / distance) * (distanceX)* elapsedTime + pAccX;
            pVelY = (ENEMY1_SPEED / distance) * (distanceY)* elapsedTime + pAccY;
         }
         this->at(i).move(pVelX, pVelY);
         distance = 0;
         distanceX = 0;
         distanceY = 0;
         pAccX = 0;
         pAccY = 0;
         //pVelX = 0;
         //pVelY = 0;

         break;
      case 2:
         if (distance < 400) {
            pAccX = (ENEMY1_ACCEL / distance) * (distanceX)* elapsedTime;
            pAccY = (ENEMY1_ACCEL / distance) * (distanceY)* elapsedTime;
            pVelX += pAccX;
            pVelY += pAccY;
         }
         else {
            pVelX = (ENEMY1_SPEED / distance) * (distanceX)* elapsedTime + pAccX;
            pVelY = (ENEMY1_SPEED / distance) * (distanceY)* elapsedTime + pAccY;
         }

         this->at(i).move(pVelX + (((float)rand() / RAND_MAX) * ENEMY1_RANDOM) - (ENEMY1_RANDOM / 2),
               pVelY + (((float)rand() / RAND_MAX) * ENEMY1_RANDOM) - (ENEMY1_RANDOM / 2));

         break;
      default:
         break;
      }
   }
}
