#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;


class Enemy : public Sprite {
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
   void update(float& elapsedTime, const Vector2f& playerPos);
};