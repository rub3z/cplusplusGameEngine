// Adapted from code used in this tutorial:
// https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php
#pragma once
#include "stdafx.h"
#include "Enemies.h"

Enemies::Enemies()
{
   
   this->assign(MAX_ENEMY1 * 4, VertexInfo());
   for (int i = 0; i < MAX_ENEMY1; i++) {
      int j = i * 4;
      this->at(j).g = 255;
      this->at(j+1).g = 255;
      this->at(j+2).g = 255;
      this->at(j+3).g = 255;

   }
   
   quadInfo.resize(MAX_ENEMY1);

   for (int i = 0; i < MAX_ENEMY1; i++) {
      quadInfo[i].index = i * 4;
   }

   for (int i = 0; i < 200; i++) {
      for (int j = 0; j < 1; j++) {
         int k = (i + j * 200) * 4;
         this->at(k).posX = i * 10; this->at(k).posY = j * 10;
         this->at(k+1).posX = i * 10 + 5; this->at(k+1).posY = j * 10;
         this->at(k+2).posX = i * 10 + 5; this->at(k+2).posY = j * 10 + 5;
         this->at(k+3).posX = i * 10; this->at(k+3).posY = j * 10 + 5;
      }
   }
}

void Enemies::update(float& elapsedTime, float& playerPosX, float& playerPosY)
{
   transform(std::execution::par,
      quadInfo.begin(), quadInfo.end(),
      quadInfo.begin(), [&](Info i) {
         VertexInfo* quad = &this->at(i.index);

         i.distanceX = playerPosX - quad[0].posX;
         i.distanceY = playerPosY - quad[0].posY;
         i.distance = sqrt(pow(i.distanceX, 2) + pow(i.distanceY, 2));

         quad[0].posX += (ENEMY1_SPEED / i.distance) * (i.distanceX) * elapsedTime;
         quad[1].posX += (ENEMY1_SPEED / i.distance) * (i.distanceX) * elapsedTime;
         quad[2].posX += (ENEMY1_SPEED / i.distance) * (i.distanceX) * elapsedTime;
         quad[3].posX += (ENEMY1_SPEED / i.distance) * (i.distanceX) * elapsedTime;

         quad[0].posY += (ENEMY1_SPEED / i.distance) * (i.distanceY) * elapsedTime;
         quad[1].posY += (ENEMY1_SPEED / i.distance) * (i.distanceY) * elapsedTime;
         quad[2].posY += (ENEMY1_SPEED / i.distance) * (i.distanceY) * elapsedTime;
         quad[3].posY += (ENEMY1_SPEED / i.distance) * (i.distanceY) * elapsedTime;

         return i;
      });
}
