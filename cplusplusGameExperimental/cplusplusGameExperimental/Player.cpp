#include "stdafx.h"
#include "Player.h"
#include "ConstantsNStuff.h"

Player::Player(int playerNum) {
   this->assign(4, VertexInfo());
   VertexInfo* vertices = &this->at(0);
   width = 30.0f;
   height = 30.0f;

   switch (playerNum) {
   case 0:
      vertices[0].posX = 960;
      vertices[0].posY = 540;
      vertices[1].posX = vertices[0].posX + width;
      vertices[1].posY = vertices[0].posY;
      vertices[2].posX = vertices[0].posX + width;
      vertices[2].posY = vertices[0].posY + height;
      vertices[3].posX = vertices[0].posX;
      vertices[3].posY = vertices[0].posY + height;

      vertices[0].r = 255;
      vertices[1].g = 255;
      vertices[2].b = 255;
      vertices[3].r = 255;
      break;
   case 1:
      vertices[0].posX = 1000;
      vertices[0].posY = 540;
      vertices[1].posX = vertices[0].posX + width;
      vertices[1].posY = vertices[0].posY;
      vertices[2].posX = vertices[0].posX + width;
      vertices[2].posY = vertices[0].posY + height;
      vertices[3].posX = vertices[0].posX;
      vertices[3].posY = vertices[0].posY + height;

      vertices[0].b = 255;
      vertices[1].b = 255;
      vertices[2].b = 255;
      vertices[3].b = 255;
      break;
   case 2:
      vertices[0].posX = 1040;
      vertices[0].posY = 540;
      vertices[1].posX = vertices[0].posX + width;
      vertices[1].posY = vertices[0].posY;
      vertices[2].posX = vertices[0].posX + width;
      vertices[2].posY = vertices[0].posY + height;
      vertices[3].posX = vertices[0].posX;
      vertices[3].posY = vertices[0].posY + height;

      vertices[0].r = 255;
      vertices[1].r = 255;
      vertices[2].r = 255;
      vertices[3].r = 255;

      vertices[0].g = 255;
      vertices[1].g = 255;
      vertices[2].g = 255;
      vertices[3].g = 255;


      break;
   case 3:
      vertices[0].posX = 1080;
      vertices[0].posY = 540;
      vertices[1].posX = vertices[0].posX + width;
      vertices[1].posY = vertices[0].posY;
      vertices[2].posX = vertices[0].posX + width;
      vertices[2].posY = vertices[0].posY + height;
      vertices[3].posX = vertices[0].posX;
      vertices[3].posY = vertices[0].posY + height;

      vertices[0].g = 255;
      vertices[1].g = 255;
      vertices[2].g = 255;
      vertices[3].g = 255;
      break;
   default:
      break;
   }

   centerX = vertices[0].posX + (width / 2);
   centerY = vertices[0].posY + (height / 2);

}

void Player::movement(float const &valX, float const &valY) {
   pMoveX = valX;
   pMoveY = valY;
}

void Player::update(float& elapsedTime) {
   VertexInfo* corners = &this->at(0);

   corners[0].posX += pMoveX * PLAYER_SPEED * elapsedTime;
   corners[0].posY += pMoveY * PLAYER_SPEED * elapsedTime;
   corners[1].posX += pMoveX * PLAYER_SPEED * elapsedTime;
   corners[1].posY += pMoveY * PLAYER_SPEED * elapsedTime;
   corners[2].posX += pMoveX * PLAYER_SPEED * elapsedTime;
   corners[2].posY += pMoveY * PLAYER_SPEED * elapsedTime;
   corners[3].posX += pMoveX * PLAYER_SPEED * elapsedTime;
   corners[3].posY += pMoveY * PLAYER_SPEED * elapsedTime;

   centerX += pMoveX * PLAYER_SPEED * elapsedTime;
   centerY += pMoveY * PLAYER_SPEED * elapsedTime;
}
