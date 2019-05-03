#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Projectile {
   Vector2f pPosition;

   Sprite pSprite;

   Texture pTexture;

   float pMoveX, pMoveY;
   
   float lifeTimeCounter;
   
public:
   Projectile();
   Sprite& getSprite();
   FloatRect& getRect();
   void shootStraight(Vector2f& pos, float& vX, float& vY);
   void shootSpread(Vector2f& pos, float& vX, float& vY);
   void update(float& elapsedTime);
};