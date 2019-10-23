// Adapted from code used in this tutorial:
// https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php
#pragma once
#include "stdafx.h"
#include "Enemies.h"

void hitEnemy2(ObjectInfo * o, ObjectInfo * that) {
   if (that->type < 2) {
      o->r = 0; o->g = 0; o->b = 0;
      o->posX = 0; o->posY = 0;
      o->collisionIndex = -1;
   }
}

Enemies::Enemies()
{
   this->assign(MAX_ENEMY1, ObjectInfo());
   for (int i = 0; i < MAX_ENEMY1; i++) {
      this->at(i).g = 255;
   }
   
   info.resize(MAX_ENEMY1);

   for (int i = 0; i < MAX_ENEMY1; i++) {
      info[i].index = i;
   }

   float space = 20.0f;
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
         ObjectInfo* o = &this->at(i.index);

         i.distanceX = playerPosX - o->posX;
         i.distanceY = playerPosY - o->posY;
         i.distance = sqrt(pow(i.distanceX, 2) + pow(i.distanceY, 2));

         o->posX += (ENEMY1_SPEED / i.distance) * (i.distanceX) * elapsedTime;
         o->posY += (ENEMY1_SPEED / i.distance) * (i.distanceY) * elapsedTime;

         return i;
      });
}
