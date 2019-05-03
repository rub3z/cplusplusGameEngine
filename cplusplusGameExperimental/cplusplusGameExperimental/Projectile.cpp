#include "stdafx.h"
#include "Projectile.h"
#include "ConstantsNStuff.h"
#include <iostream>

using namespace std;

Projectile::Projectile() {
   pTexture.loadFromFile("Player.png");
   pSprite.setTexture(pTexture);
   pSprite.setOrigin(5, 5);
   //pSprite.setScale(0.5f, 0.5f);
   pSprite.scale(2.0f, 2.0f);
   //pSprite.setColor(Color(255, 128, 0, 255));
   lifeTimeCounter = 0.0;
}

Sprite& Projectile::getSprite() {
   return pSprite;
}

FloatRect& Projectile::getRect() {
   return pSprite.getGlobalBounds();
}

void Projectile::shootStraight(Vector2f& pos, float& vX, float& vY) {
   pPosition = pos;
   pMoveX = (vX / sqrtf(pow(vX, 2) + pow(vY, 2))) * 100;
   pMoveY = (vY / sqrtf(pow(vX, 2) + pow(vY, 2))) * 100;
   lifeTimeCounter = 0;
}

void Projectile::shootSpread(Vector2f& pos, float& vX, float& vY) {
   pPosition = pos;
   pMoveX = (vX / (sqrtf(pow(vX, 2) + pow(vY, 2)))) * 100 + 
            (((float)rand() / RAND_MAX) * BULLET_SPREAD) - (BULLET_SPREAD / 2);
   pMoveY = (vY / (sqrtf(pow(vX, 2) + pow(vY, 2)))) * 100 + 
            (((float)rand() / RAND_MAX) * BULLET_SPREAD) - (BULLET_SPREAD / 2);
   lifeTimeCounter = 0;
}

void Projectile::update(float& elapsedTime) {
   pPosition.x += pMoveX * BULLET_SPEED * elapsedTime;
   pPosition.y += pMoveY * BULLET_SPEED * elapsedTime;
   lifeTimeCounter += elapsedTime;
   if (lifeTimeCounter > BULLET_LIFETIME) { 
      pMoveX = 0; pMoveY = 0; 
      lifeTimeCounter = 0; 
   }
   if (pMoveX == 0 && pMoveY == 0) { 
      pPosition.x = -1337; pPosition.y = -1337; }

   pSprite.setPosition(pPosition);
}
