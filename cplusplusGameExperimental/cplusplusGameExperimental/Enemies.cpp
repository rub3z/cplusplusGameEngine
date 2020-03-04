#pragma once
#include "stdafx.h"
#include "Enemies.h"

void hitEnemy2(GameObject * o, GameObject * that) {
   if (that->type < 2) {
      int r = rand();
      switch (r % 4) {
      case 0:
         o->posX = (float) (r % 1920);
         o->posY = -128.0f;
         break;
      case 1:
         o->posX = 2048.0f;
         o->posY = (float) (r % 1080);
         break;
      case 2:
         o->posX = (float) (r % 1920);
         o->posY = 1208.0f;
         break;
      case 3:
         o->posX = -128.0f;
         o->posY = (float)(r % 1080);
         break;
      default: break;
      }

      switch (r % 3) {
      case 0: o->r = r % 128 + 128; break;
      case 1: o->g = r % 128 + 128; break;
      case 2: o->b = r % 128 + 128; break;
      default: break;
      }

      o->height = (float) (r % 20) + 10.0f;
      o->width = o->height;

      o->collisionIndex = -1;
   }
   
}

void hitEnemy3(GameObject * o, GameObject * that) {
   if (that->type < 2) {
      o->r = 255; o->g = 0; o->b = 128;
   }
}

void Enemies::doit() {
   vT[0] = hitEnemy3;
}

Enemies::Enemies()
{
   this->assign(MAX_ENEMY1, GameObject());
   for (int i = 0; i < MAX_ENEMY1; i++) {
      this->at(i).g = 255;
   }
   
   info.resize(MAX_ENEMY1);

   for (int i = 0; i < MAX_ENEMY1; i++) {
      info[i].index = i;
   }

   float space = 40.0f;
   float width = 15.0f;
   float height = 15.0f;

   float px = 0.0f; float py = 0.0f;

   for (int i = 0; i < MAX_ENEMY1; i++) {
      this->at(i).posX = px;
      this->at(i).posY = py;
      px += space;
      if (px >= 1900.0f) {
         px = 0.0f; py += space;
      }
      this->at(i).width = width; this->at(i).height = height;
   }

   vT[0] = hitEnemy2;

   for (int i = 0; i < MAX_ENEMY1; i++) {
      this->at(i).vTable = vT;
      this->at(i).type = 3;
   }
}
 
void Enemies::update(float& elapsedTime, float& playerPosX, float& playerPosY)
{
   transform(std::execution::par,
      info.begin(), info.end(),
      info.begin(), [&](Info i) {
         GameObject* o = &this->at(i.index);

         i.distanceX = playerPosX - o->posX;
         i.distanceY = playerPosY - o->posY;
         i.distance = sqrt(pow(i.distanceX, 2) + pow(i.distanceY, 2));

         o->posX += (ENEMY1_SPEED / i.distance) * (i.distanceX) * elapsedTime;
         o->posY += (ENEMY1_SPEED / i.distance) * (i.distanceY) * elapsedTime;

         if (o->collisionIndex == -1) {
            o->flag = true;
         }

         return i;
      });

   flagged.clear();
   for (int i = 0; i < MAX_ENEMY1; i++) {
      if (this->at(i).flag) {
         flagged.push_back(&this->at(i));
         this->at(i).flag = false;
      }
   }

}
