#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Player : public Sprite { // I like Sprite. Caffeine-free.
   Texture pTexture;
   // Movement components in x and y directions.
   float pMoveX, pMoveY;
   
public:
   CircleShape circle;

   Player(int playerNum);
   
   void movement(float const &valX, float const &valY);

   void update(float& elapsedTime);
};