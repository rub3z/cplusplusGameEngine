#include "stdafx.h"
#include "Projectiles.h"
#include "stdafx.h"
#include "Projectiles.h"
#include "ConstantsNStuff.h"
#include <iostream>

using namespace std;

Projectiles::Projectiles()
{
   width = 10;
   height = 10;
   this->assign(MAX_BULLETS * 4, VertexInfo());
   quadInfo.resize(MAX_BULLETS);

   for (int i = 0; i < MAX_BULLETS; i++) {
      quadInfo[i].index = i * 4;
   }

   for (int i = 0; i < MAX_BULLETS; i++) {
      VertexInfo* v = &this->at(quadInfo[i].index);
      v[0].r = 255;
      v[1].r = 255;
      v[2].r = 255;
      v[3].r = 255;

      v[0].posX = 10;
      v[1].posX = v[0].posX + width;
      v[2].posX = v[0].posX + width;
      v[3].posX = v[0].posX;

      v[0].posY = 10;
      v[1].posY = v[0].posY;
      v[2].posY = v[0].posY + height;
      v[3].posY = v[0].posY + height;
   }

   pIterator = 0;
}

// Credit to Tommy So for fixing shoot methods.
void Projectiles::shootStraight(float& playerPosX, float& playerPosY, 
                                float & vX, float & vY)
{
   VertexInfo* b = &this->at(quadInfo[pIterator].index);

   b[0].posX = playerPosX;
   b[0].posY = playerPosY;
   b[1].posX = playerPosX + width;
   b[1].posY = playerPosY;
   b[2].posX = playerPosX + width;
   b[2].posY = playerPosY + height;
   b[3].posX = playerPosX;
   b[3].posY = playerPosY + height;

   b[0].r = 255;
   b[1].r = 255;
   b[2].r = 255;
   b[3].r = 255;


   quadInfo[pIterator].moveX = (vX / sqrtf(pow(vX, 2) + pow(vY, 2))) * 100;
   quadInfo[pIterator].moveY = (vY / sqrtf(pow(vX, 2) + pow(vY, 2))) * 100;
   quadInfo[pIterator].lifetime = 0;
   
   pIterator++;
   if (pIterator == MAX_BULLETS) pIterator = 0;
}

void Projectiles::shootSpread(float& playerPosX, float& playerPosY,
   float& vX, float& vY)
{
   for (int i = 0; i < SPREAD_BULLETS; i++) {
      VertexInfo* b = &this->at(quadInfo[pIterator].index);

      b[0].posX = playerPosX;
      b[0].posY = playerPosY;
      b[1].posX = playerPosX + width;
      b[1].posY = playerPosY;
      b[2].posX = playerPosX + width;
      b[2].posY = playerPosY + height;
      b[3].posX = playerPosX;
      b[3].posY = playerPosY + height;

      b[0].b = 255;
      b[1].b = 255;
      b[2].b = 255;
      b[3].b = 255;

      quadInfo[pIterator].moveX = (vX / (sqrtf(pow(vX, 2) + pow(vY, 2)))) * 100 +
         (((float)rand() / RAND_MAX) * BULLET_SPREAD) - (BULLET_SPREAD / 2);
      quadInfo[pIterator].moveY = (vY / (sqrtf(pow(vX, 2) + pow(vY, 2)))) * 100 +
         (((float)rand() / RAND_MAX) * BULLET_SPREAD) - (BULLET_SPREAD / 2);
      quadInfo[pIterator].lifetime = 0;

      pIterator++;
      if (pIterator == MAX_BULLETS) pIterator = 0;
   }
}

void Projectiles::collisionCheck(Sprite & other)
{

}

void Projectiles::update(float & elapsedTime)
{
   transform(std::execution::par,
      quadInfo.begin(), quadInfo.end(),
      quadInfo.begin(), [&](Info i) {
         VertexInfo* quad = &this->at(i.index);

         quad[0].posX += i.moveX * BULLET_SPEED * elapsedTime;
         quad[1].posX += i.moveX * BULLET_SPEED * elapsedTime;
         quad[2].posX += i.moveX * BULLET_SPEED * elapsedTime;
         quad[3].posX += i.moveX * BULLET_SPEED * elapsedTime;
         
         quad[0].posY += i.moveY * BULLET_SPEED * elapsedTime;
         quad[1].posY += i.moveY * BULLET_SPEED * elapsedTime;
         quad[2].posY += i.moveY * BULLET_SPEED * elapsedTime;
         quad[3].posY += i.moveY * BULLET_SPEED * elapsedTime;

         i.lifetime += elapsedTime;
         if (i.lifetime > BULLET_LIFETIME) {
            i.moveX = 0;
            i.moveY = 0;
         }

         if (i.moveX == 0 && i.moveY == 0) {
            quad[0].posX = 10;
            quad[1].posX = quad[0].posX + width;
            quad[2].posX = quad[0].posX + width;
            quad[3].posX = quad[0].posX;

            quad[0].posY = 10;
            quad[1].posY = quad[0].posY;
            quad[2].posY = quad[0].posY + height;
            quad[3].posY = quad[0].posY + height;

            quad[0].r = 0;
            quad[1].r = 0;
            quad[2].r = 0;
            quad[3].r = 0;

            quad[0].b = 0;
            quad[1].b = 0;
            quad[2].b = 0;
            quad[3].b = 0;
         }
 
         return i;
      });
}
