#include "stdafx.h"
#include "Projectiles.h"

void hitBullet(GameObject * o, GameObject * that) {
   if (that->type > 1) {
      o->r = 0; o->g = 0; o->b = 0;
      o->posX = -128; o->posY = -128;
      o->collisionIndex = -1;
   }
}

Projectiles::Projectiles()
{
   width = 10.0f;
   height = 10.0f;
   this->assign(MAX_BULLETS, GameObject());
   info.resize(MAX_BULLETS);

   vT[0] = hitBullet;

   for (int i = 0; i < MAX_BULLETS; i++) {
      info[i].index = i;
      info[i].shot = false;
   }

   for (int i = 0; i < MAX_BULLETS; i++) {
      this->at(i).r = 255;
      this->at(i).posX = -128;
      this->at(i).posY = -128;
      this->at(i).width = width;
      this->at(i).height = height;
      this->at(i).vTable = vT;
      this->at(i).type = 1;
   }

   pIterator = 0;
}

// Credit to Tommy So for fixing shoot methods.
GameObject& Projectiles::shootStraight(float& playerPosX, float& playerPosY,
   const float& vX, const float& vY)
{
   GameObject* b = &this->at(info[pIterator].index);

   b->posX = playerPosX;
   b->posY = playerPosY;
   
   b->r = 255;
   b->b = 0;
   b->flag = true;

   float rf1 = ((rand() % BULLET_SPREAD) - (BULLET_SPREAD / 2)) / 100.0f;
   
   float vXU = (vX / (sqrtf(pow(vX, 2) + pow(vY, 2))));
   float vYU = (vY / (sqrtf(pow(vX, 2) + pow(vY, 2))));
   float vXUr = vXU * cos(rf1) - vYU * sin(rf1);
   float vYUr = vXU * sin(rf1) + vYU * cos(rf1);
   
   info[pIterator].moveX = vXUr * 100.0f;
   info[pIterator].moveY = vYUr * 100.0f;

   info[pIterator].lifetime = 0;
   info[pIterator].shot = true;

   pIterator++;
   if (pIterator == MAX_BULLETS) pIterator = 0;
   return *b;
}

GameObject& Projectiles::shootSpread(float& playerPosX, float& playerPosY,
   float& vX, float& vY)
{
   GameObject* b = &this->at(info[pIterator].index);

   b->posX = playerPosX;
   b->posY = playerPosY;

   b->r = 0;
   b->b = 255;
   b->flag = true;

   float rf1 = ((rand() % BULLET_SPREAD) - (BULLET_SPREAD / 2)) / 100.0f;

   float vXU = (vX / (sqrtf(pow(vX, 2) + pow(vY, 2))));
   float vYU = (vY / (sqrtf(pow(vX, 2) + pow(vY, 2))));
   float vXUr = vXU * cos(rf1) - vYU * sin(rf1);
   float vYUr = vXU * sin(rf1) + vYU * cos(rf1);

   info[pIterator].moveX = vXUr * 100.0f;
   info[pIterator].moveY = vYUr * 100.0f;

   info[pIterator].lifetime = 0;
   info[pIterator].shot = true;

   pIterator++;
   if (pIterator == MAX_BULLETS) pIterator = 0;
   return *b;
}

void Projectiles::update(float& elapsedTime)
{
   transform(std::execution::par,
      info.begin(), info.end(),
      info.begin(), [&](Info i) {
         GameObject* b = &this->at(i.index);
         if (i.shot) {
            b->posX += i.moveX * BULLET_SPEED * elapsedTime;
            b->posY += i.moveY * BULLET_SPEED * elapsedTime;

            i.lifetime += elapsedTime;
            if (i.lifetime > BULLET_LIFETIME) {
               i.shot = false;
               i.moveX = 0;
               i.moveY = 0;
               b->posX = 0;
               b->posY = 0;
               b->r = 0; b->g = 0; b->b = 0;
               b->collisionIndex = -1;
            }
         }
         return i;
      });

   flagged.clear();
   for (int i = 0; i < MAX_BULLETS; i++) {
      if (this->at(i).flag) {
         flagged.push_back(&this->at(i));
         this->at(i).flag = false;
      }
   }
}
