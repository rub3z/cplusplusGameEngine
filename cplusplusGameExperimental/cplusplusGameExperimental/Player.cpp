#include "stdafx.h"
#include "Player.h"

Player::Player(int playerNum) {
   width = 30.0f;
   height = 30.0f;

   pMoveX = 0.0f;
   pMoveY = 0.0f;

   switch (playerNum) {
   case 0:
      posX = 960; posY = 540;
      r = 255; g = 255; b = 255;
      break;
   case 1:
      posX = 1000; posY = 540;
      r = 255; g = 255; b = 255;
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

}

void Player::movement(float const &valX, float const &valY) {
   //pMoveX = valX; 
   //pMoveY = valY;
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

   centerX += pMoveX * PLAYER_SPEED * elapsedTime;
   centerY += pMoveY * PLAYER_SPEED * elapsedTime;
}
