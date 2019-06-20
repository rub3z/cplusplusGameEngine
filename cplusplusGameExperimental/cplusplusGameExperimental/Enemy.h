#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

using namespace sf;


class Enemy : public GameObject {
   Texture pTexture;

   int enemyType;
   float pVelX, pVelY;
   float pAccX, pAccY;
   float distance;
   float distanceX;
   float distanceY;

public:
   Enemy();
   Enemy(int type);
   void hit(FloatRect& other);
   void hit();
   void update(float& elapsedTime, float& playerPosX, float& playerPosY);
};