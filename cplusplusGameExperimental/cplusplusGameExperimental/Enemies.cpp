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
   
   quadInfo.resize(MAX_ENEMY1);

   for (int i = 0; i < MAX_ENEMY1; i++) {
      quadInfo[i].index = i;
   }

   int space = 10;
   int width = 5;

   for (int i = 0; i < 200; i++) {
      for (int j = 0; j < 200; j++) {
         int k = (i + j * 200);
         this->at(k).posX = i * space; this->at(k).posY = j * space;
         this->at(k).width = width; this->at(k).height = width;
      }
   }
}

void Enemies::update(float& elapsedTime, float& playerPosX, float& playerPosY)
{
   transform(std::execution::par,
      quadInfo.begin(), quadInfo.end(),
      quadInfo.begin(), [&](Info i) {
         ObjectInfo* o = &this->at(i.index);

         i.distanceX = playerPosX - o->posX;
         i.distanceY = playerPosY - o->posY;
         i.distance = sqrt(pow(i.distanceX, 2) + pow(i.distanceY, 2));

         o->posX += (ENEMY1_SPEED / i.distance) * (i.distanceX) * elapsedTime;
         o->posY += (ENEMY1_SPEED / i.distance) * (i.distanceY) * elapsedTime;
         
         return i;
      });
}
