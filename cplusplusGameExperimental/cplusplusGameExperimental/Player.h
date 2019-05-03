#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Player {
   Vector2f pPosition;

   Sprite pSprite;

   Texture pTexture;

   // Movement components in x and y directions.
   float pMoveX, pMoveY;

   // Or we can use a vector velocity variable if we're feeling fancy and want
   // to make our code even more arcane and less readable.
   Vector2f pVelocity;

public:
   Player(int playerNum);
   Sprite& getSprite(); // I like Sprite. Caffeine-free.

   Vector2f& getPosition();

   void move(float const &valX, float const &valY);

   void update(float& elapsedTime);

};