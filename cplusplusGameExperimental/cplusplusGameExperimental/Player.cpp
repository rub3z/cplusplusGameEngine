#include "stdafx.h"
#include "Player.h"
#include "ConstantsNStuff.h"

Player::Player(int playerNum) {
   pTexture.loadFromFile("Player.png");
   circle = CircleShape(400);
   circle.setOutlineColor(Color::Red);
   circle.setFillColor(Color::Transparent);
   circle.setOutlineThickness(3.0f);
   //circle.setOrigin(282.84f, 282.84f);
   circle.setOrigin(400, 400);

   this->setTexture(pTexture);
   this->setOrigin(5, 5);
   this->scale(6, 6);
   
   switch (playerNum) {
   case 0:
      circle.setPosition(800, 800);
      this->setPosition(800, 800);
      this->setColor(Color::Red);
      break;
   case 1:
      this->setPosition(850, 800);
      this->setColor(Color::Blue);
      break;
   case 2:
      this->setPosition(900, 800);
      this->setColor(Color::Green);
      break;
   case 3:
      this->setPosition(950, 800);
      this->setColor(Color::Yellow);
      break;

   }
}

void Player::movement(float const &valX, float const &valY) {
   pMoveX = valX;
   pMoveY = valY;
}

void Player::update(float& elapsedTime) {
   this->move(pMoveX * PLAYER_SPEED * elapsedTime,
              pMoveY * PLAYER_SPEED * elapsedTime);
   circle.move(pMoveX * PLAYER_SPEED * elapsedTime,
               pMoveY * PLAYER_SPEED * elapsedTime);
}
