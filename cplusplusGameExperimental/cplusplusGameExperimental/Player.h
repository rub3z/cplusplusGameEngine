#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameObject.h"
#include "ObjectInfo.h"

using namespace sf;
using namespace std;

class Player : public ObjectInfo {
   // Movement components in x and y directions.
   float pMoveX, pMoveY;
   //int width, height;
   
public:
   float centerX, centerY;

   Player(int playerNum);
   
   void movement(float const &valX, float const &valY);

   void update(float& elapsedTime);
};