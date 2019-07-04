#pragma once
using namespace sf;

class Projectile : public Sprite {
   Texture pTexture;

   float pMoveX, pMoveY;
   
   float lifeTimeCounter;
   
public:
   Projectile();
   void shootStraight(const Vector2f& pos, float& vX, float& vY);
   void shootSpread(const Vector2f& pos, float& vX, float& vY);
   void update(float& elapsedTime);
};