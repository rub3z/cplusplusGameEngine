// Adapted from code used in this tutorial:
// https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php
#pragma once
#include "stdafx.h"
#include "Enemies.h"

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

   int space = 20;
   float width = 15.0f;
   float height = 15.0f;

   //for (int i = 0; i < 100; i++) {
   //   this->at(i).posX = (float)(i * space);
   //   this->at(i).posY = 100;
   //   this->at(i).width = width; this->at(i).height = height;
   //}

   for (int i = 0; i < 100; i++) {
      for (int j = 0; j < 10; j++) {
         int k = (i + j * 100);
         this->at(k).posX = (float) (i * space); 
         this->at(k).posY = (float) (j * space);
         this->at(k).width = width; this->at(k).height = height;
      }
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
