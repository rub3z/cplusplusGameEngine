#include "stdafx.h"
#include "Player.h"
#include "ConstantsNStuff.h"


Player::Player(int playerNum) {
   pTexture.loadFromFile("Player.png");
   pSprite.setTexture(pTexture);
   pSprite.setOrigin(5, 5);
   pSprite.scale(10, 10);
   switch (playerNum) {
   case 0:
      pPosition.x = 800;
      pPosition.y = 800;
      pSprite.setColor(Color::Red);
      break;
   case 1:
      pPosition.x = 850;
      pPosition.y = 800;
      pSprite.setColor(Color::Blue);
      break;
   case 2:
      pPosition.x = 900;
      pPosition.y = 800;
      pSprite.setColor(Color::Green);
      break;
   case 3:
      pPosition.x = 950;
      pPosition.y = 800;
      pSprite.setColor(Color::Yellow);
      break;

   }
}

Sprite& Player::getSprite() {
   return pSprite;
}

Vector2f& Player::getPosition() {
   return pPosition;
}

void Player::move(float const &valX, float const &valY) {
   pMoveX = valX;
   pMoveY = valY;
}

void Player::update(float& elapsedTime) {
   pPosition.x += pMoveX * PLAYER_SPEED * elapsedTime;
   pPosition.y += pMoveY * PLAYER_SPEED * elapsedTime;

   pSprite.setPosition(pPosition);
}
