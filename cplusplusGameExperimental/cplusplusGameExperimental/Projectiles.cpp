#include "stdafx.h"
#include "Projectiles.h"
#include <iostream>

using namespace std;

Projectiles::Projectiles()
{
   width = 10;
   height = 10;
   this->assign(MAX_BULLETS, ObjectInfo());
   quadInfo.resize(MAX_BULLETS);

   for (int i = 0; i < MAX_BULLETS; i++) {
      quadInfo[i].index = i;
   }

   for (int i = 0; i < MAX_BULLETS; i++) {
      this->at(i).r = 255;
      this->at(i).posX = 10;
      this->at(i).posY = 10;
      this->at(i).width = width;
      this->at(i).height = height;
   }

   pIterator = 0;
}

// Credit to Tommy So for fixing shoot methods.
ObjectInfo& Projectiles::shootStraight(float& playerPosX, float& playerPosY,
   float& vX, float& vY)
{
   ObjectInfo* b = &this->at(quadInfo[pIterator].index);

   b->posX = playerPosX;
   b->posY = playerPosY;

   b->r = 255;

   quadInfo[pIterator].moveX = (vX / sqrtf(pow(vX, 2) + pow(vY, 2))) * 100;
   quadInfo[pIterator].moveY = (vY / sqrtf(pow(vX, 2) + pow(vY, 2))) * 100;
   quadInfo[pIterator].lifetime = 0;

   pIterator++;
   if (pIterator == MAX_BULLETS) pIterator = 0;
   return *b;
}

ObjectInfo& Projectiles::shootSpread(float& playerPosX, float& playerPosY,
   float& vX, float& vY)
{
   ObjectInfo* b = &this->at(quadInfo[pIterator].index);

   b->posX = playerPosX;
   b->posY = playerPosY;

   b->b = 255;

   quadInfo[pIterator].moveX = (vX / (sqrtf(pow(vX, 2) + pow(vY, 2)))) * 100 +
      (((float)rand() / RAND_MAX) * BULLET_SPREAD) - (BULLET_SPREAD / 2);
   quadInfo[pIterator].moveY = (vY / (sqrtf(pow(vX, 2) + pow(vY, 2)))) * 100 +
      (((float)rand() / RAND_MAX) * BULLET_SPREAD) - (BULLET_SPREAD / 2);
   quadInfo[pIterator].lifetime = 0;

   pIterator++;
   if (pIterator == MAX_BULLETS) pIterator = 0;
   return *b;
}

void Projectiles::collisionCheck(Sprite& other)
{

}

void Projectiles::update(float& elapsedTime)
{
   transform(std::execution::seq,
      quadInfo.begin(), quadInfo.end(),
      quadInfo.begin(), [&](Info i) {
         ObjectInfo* b = &this->at(i.index);

         b->posX += i.moveX * BULLET_SPEED * elapsedTime;
         b->posY += i.moveY * BULLET_SPEED * elapsedTime;

         i.lifetime += elapsedTime;
         if (i.lifetime > BULLET_LIFETIME) {
            i.moveX = 0;
            i.moveY = 0;
            b->posX = 10;
            b->posY = 10;
            b->r = 0; b->g = 0; b->b = 0;
         }
         return i;
      });
}
