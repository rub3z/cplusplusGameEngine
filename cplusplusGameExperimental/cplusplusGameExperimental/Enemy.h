#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;


class Enemy {
   Vector2f pPosition;

   Sprite pSprite;

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
   Sprite& getSprite();
   Vector2f& getPosition();
   void hit(FloatRect& other);
   void hit();
   void update(float& elapsedTime, Vector2f& playerPos);
};