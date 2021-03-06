#include "stdafx.h"
#include "Projectiles.h"

void updateBullet1(GameObject * b, BulletInfo & i, float & elapsedTime) {
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
         b->collideable = false;
      }
   }
}


// Credit to Tommy So for fixing shoot methods.
void shoot1(GameObject * b, BulletInfo* in, float& playerPosX, float& playerPosY,
   const float& vX, const float& vY) {
   b->posX = playerPosX;
   b->posY = playerPosY;

   b->r = 255;

   in->flag = true;

   float vXU = (vX / (sqrtf(pow(vX, 2) + pow(vY, 2))));
   float vYU = (vY / (sqrtf(pow(vX, 2) + pow(vY, 2))));
   
   in->moveX = vXU * 100.0f;
   in->moveY = vYU * 100.0f;

   in->lifetime = 0;
   in->shot = true;
}

void shoot2(GameObject* b, BulletInfo* in, float& playerPosX, float& playerPosY,
   const float& vX, const float& vY) {
   b->posX = playerPosX;
   b->posY = playerPosY;

   b->b = 255;
  
   in->flag = true;

   float rf1 = ((rand() % BULLET_SPREAD) - (BULLET_SPREAD / 2)) / 100.0f;

   float vXU = (vX / (sqrtf(pow(vX, 2) + pow(vY, 2))));
   float vYU = (vY / (sqrtf(pow(vX, 2) + pow(vY, 2))));
   float vXUr = vXU * cos(rf1) - vYU * sin(rf1);
   float vYUr = vXU * sin(rf1) + vYU * cos(rf1);

   in->moveX = vXUr * 100.0f;
   in->moveY = vYUr * 100.0f;

   in->lifetime = 0;
   in->shot = true;
}

void hitBullet(GameObject * o, GameObject * that) {
   if (that->type > 1) {
      o->r = 0; o->g = 0; o->b = 0;
      o->posX = -128; o->posY = -128;
      o->collideable = false;
   }
}

Projectiles::Projectiles()
{
   width = 10.0f;
   height = 10.0f;
   this->assign(MAX_BULLETS, GameObject());
   info.resize(MAX_BULLETS);

   vT[UPDATE_FUNC_ID] = updateBullet1;
   vT[HIT_FUNC_ID] = hitBullet;
   vT[SHOOT_FUNC_ID] = shoot1;

   for (size_t i = 0; i < MAX_BULLETS; i++) {
      info[i].index = i;
      info[i].shot = false;
   }

   for (size_t i = 0; i < MAX_BULLETS; i++) {
      this->at(i).posX = -128;
      this->at(i).posY = -128;
      this->at(i).width = width;
      this->at(i).height = height;
      this->at(i).vTable = vT;
      this->at(i).type = 1;
   }

   pIterator = 0;
}

void Projectiles::shoot(float& posX, float& posY,
   const float& vX, const float& vY, bool type, float & fireRateDelta)
{
   vT[SHOOT_FUNC_ID] = type ? shoot2 : shoot1;
   size_t numberOfProjectiles = type ? SPREAD_BULLETS : 1;

   if (type && fireRateDelta >= SPREAD_FIRE_RATE) {
      for (size_t i = 0; i < numberOfProjectiles; i++) {
         GameObject* b = &this->at(info[pIterator].index);
         BulletInfo* in = &info[pIterator];
         ((void(*)(GameObject*, BulletInfo*, float&, float&, const float&, const float&))
            b->vTable[SHOOT_FUNC_ID])(b, in, posX, posY, vX, vY);
         pIterator++;
         if (pIterator == MAX_BULLETS) pIterator = 0;
      }
      fireRateDelta = 0.0f;
   }
   else if (!type && fireRateDelta >= RAPID_FIRE_RATE) {
      GameObject* b = &this->at(info[pIterator].index);
      BulletInfo* in = &info[pIterator];
      ((void(*)(GameObject*, BulletInfo*, float&, float&, const float&, const float&))
         b->vTable[SHOOT_FUNC_ID])(b, in, posX, posY, vX, vY);
      pIterator++;
      if (pIterator == MAX_BULLETS) pIterator = 0;
      fireRateDelta = 0.0f;
   }
}

void Projectiles::update(float& elapsedTime)
{
   transform(std::execution::par,
      info.begin(), info.end(),
      info.begin(), [&](BulletInfo i) {
         GameObject* b = &this->at(i.index);
         ((void(*)(GameObject*, BulletInfo&, float&))
            b->vTable[UPDATE_FUNC_ID])(b, i, elapsedTime);
         return i;
      });

   flagged.clear();
   for (size_t i = 0; i < MAX_BULLETS; i++) {
      if (info.at(i).flag) {
         flagged.push_back(&this->at(i));
         info.at(i).flag = false;
      }
   }
}
