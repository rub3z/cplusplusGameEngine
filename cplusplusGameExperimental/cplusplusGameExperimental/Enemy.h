#pragma once
#include "ObjectInfo.h"

using namespace sf;


class Enemy : public ObjectInfo {
   int enemyType;
   float pVelX, pVelY;
   float pAccX, pAccY;
   float distance;
   float distanceX;
   float distanceY;

public:
   Enemy();
   Enemy(int type);
   void hit();
   void update(float& elapsedTime, float& playerPosX, float& playerPosY);
};