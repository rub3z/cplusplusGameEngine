#include "stdafx.h"
#include "Projectile.h"
#include <iostream>

using namespace std;

Projectile::Projectile() {
   pTexture.loadFromFile("Player.png");
   this->setTexture(pTexture);
   this->setOrigin(5, 5);
   this->scale(6, 6);
   lifeTimeCounter = 0.0;
}

void Projectile::shootStraight(const Vector2f& pos, float& vX, float& vY) {
   this->setPosition(pos);
   pMoveX = (vX / sqrtf(pow(vX, 2) + pow(vY, 2))) * 100;
   pMoveY = (vY / sqrtf(pow(vX, 2) + pow(vY, 2))) * 100;
   lifeTimeCounter = 0;
}

void Projectile::shootSpread(const Vector2f& pos, float& vX, float& vY) {
   this->setPosition(pos);
   pMoveX = (vX / (sqrtf(pow(vX, 2) + pow(vY, 2)))) * 100 +
            (((float)rand() / RAND_MAX) * BULLET_SPREAD) - (BULLET_SPREAD / 2);
   pMoveY = (vY / (sqrtf(pow(vX, 2) + pow(vY, 2)))) * 100 + 
            (((float)rand() / RAND_MAX) * BULLET_SPREAD) - (BULLET_SPREAD / 2);
   lifeTimeCounter = 0;
}

void Projectile::update(float& elapsedTime) {
   this->move(pMoveX * BULLET_SPEED * elapsedTime,
              pMoveY * BULLET_SPEED * elapsedTime);
   lifeTimeCounter += elapsedTime;
   if (lifeTimeCounter > BULLET_LIFETIME) { 
      pMoveX = 0; pMoveY = 0; 
      lifeTimeCounter = 0; 
   }
   if (pMoveX == 0 && pMoveY == 0)
      this->setPosition(-1337, -1337);
   
}
