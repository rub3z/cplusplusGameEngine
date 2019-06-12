#include "stdafx.h"
#include "Projectiles.h"
#include "stdafx.h"
#include "Projectiles.h"
#include "ConstantsNStuff.h"
#include <iostream>

using namespace std;

Projectiles::Projectiles()
{
   pTexture.loadFromFile("Player.png");
   baseSprite.setTexture(pTexture);
   baseSprite.setOrigin(5, 5);
   baseSprite.scale(1, 1);
   
   this->assign(MAX_BULLETS, baseSprite);

   for (int i = 0; i < MAX_BULLETS; i++)
   {
      moveX[i] = 0; moveY[i] = 0; lifeTimeCounter[i] = 0;
   }
   
   pIterator = 0;
   
}

// Credit to Tommy So for fixing shoot methods.
void Projectiles::shootStraight(float& posX, float& posY, float & vX, float & vY)
{
   //this->at(pIterator).setPosition(pos);
   this->at(pIterator).posX = posX;
   this->at(pIterator).posY = posY;


   moveX[pIterator] = (vX / sqrtf(pow(vX, 2) + pow(vY, 2))) * 100;
   moveY[pIterator] = (vY / sqrtf(pow(vX, 2) + pow(vY, 2))) * 100;
   lifeTimeCounter[pIterator] = 0;
   pIterator++;
   if (pIterator == MAX_BULLETS) pIterator = 0;
}

void Projectiles::shootSpread(float& posX, float& posY, float & vX, float & vY)
{
   for (int i = 0; i < SPREAD_BULLETS; i++) {
      //this->at(pIterator).setPosition(pos);
      this->at(pIterator).posX = posX;
      this->at(pIterator).posY = posY;

      moveX[pIterator] = (vX / (sqrtf(pow(vX, 2) + pow(vY, 2)))) * 100 +
         (((float)rand() / RAND_MAX) * BULLET_SPREAD) - (BULLET_SPREAD / 2);
      moveY[pIterator] = (vY / (sqrtf(pow(vX, 2) + pow(vY, 2)))) * 100 +
         (((float)rand() / RAND_MAX) * BULLET_SPREAD) - (BULLET_SPREAD / 2);
      lifeTimeCounter[pIterator] = 0;
      pIterator++;
      if (pIterator == MAX_BULLETS) pIterator = 0;
   }
}

void Projectiles::collisionCheck(Sprite & other)
{

}

void Projectiles::update(float & elapsedTime)
{
   for (int i = 0; i < MAX_BULLETS; i++) {
      //this->at(i).move(moveX[i] * BULLET_SPEED * elapsedTime,
      //   moveY[i] * BULLET_SPEED * elapsedTime);
      this->at(i).posX += moveX[i] * BULLET_SPEED * elapsedTime;
      this->at(i).posY += moveY[i] * BULLET_SPEED * elapsedTime;
      lifeTimeCounter[i] += elapsedTime;
      if (lifeTimeCounter[i] > BULLET_LIFETIME) {
         moveX[i] = 0; 
         moveY[i] = 0;
         lifeTimeCounter[i] = 0;
      }
      if (moveX[i] == 0 && moveY[i] == 0) {
         //this->at(i).setPosition(-1337, -1337);
         this->at(i).posX = -1337;
         this->at(i).posY = -1337;
      }
   }
}
