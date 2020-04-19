#include "stdafx.h"
#include "Player.h"

void hitPlayer(GameObject * o, GameObject * that) {
   if (that->type > 1) {
      o->r = 0; o->g = 0; o->b = 0;
      o->collisionIndex = -1;
   }
}

Player::Player(int playerNum) {
   width = 30.0f;
   height = 30.0f;

   pMoveX = 0.0f;
   pMoveY = 0.0f;
   fireRateDelta = 0.0f;

   switch (playerNum) {
   case 0:
      posX = 960; posY = 540;
      r = 255; g = 0; b = 0;
      break;
   case 1:
      posX = 1000; posY = 540;
      r = 0; g = 0; b = 255;
      break;
   case 2:
      posX = 1040; posY = 540;
      r = 255; g = 255; b = 255;
      break;
   case 3:
      posX = 1080; posY = 540;
      r = 255; g = 255; b = 255;
      break;
   default:
      break;
   }

   centerX = posX + (width / 2);
   centerY = posY + (height / 2);

   vT[0] = hitPlayer;

   vTable = vT;

   type = 0;
}

void Player::movement(float const &valX, float const &valY) {
   pMoveX = valX == 0.0 ?
      0.0f :
      valX / sqrtf(pow(valX, 2) + pow(valY, 2)) * 100;
   pMoveY = valY == 0.0 ?
      0.0f :
      valY / sqrtf(pow(valX, 2) + pow(valY, 2)) * 100;
}

void Player::update(float& elapsedTime) {
   posX += pMoveX * PLAYER_SPEED * elapsedTime;
   posY += pMoveY * PLAYER_SPEED * elapsedTime;

   centerX = posX + (width / 2);
   centerY = posY + (height / 2);
}
