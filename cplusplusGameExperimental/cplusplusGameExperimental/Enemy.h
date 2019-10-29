#pragma once
#include "GameObject.h"

class Enemy : public GameObject {
   int enemyType;
   float pVelX, pVelY;
   float pAccX, pAccY;
   float distance;
   float distanceX;
   float distanceY;

   void * vT[1];

public:
   Enemy();
   Enemy(int type);
   void update(float& elapsedTime, float& playerPosX, float& playerPosY);
};