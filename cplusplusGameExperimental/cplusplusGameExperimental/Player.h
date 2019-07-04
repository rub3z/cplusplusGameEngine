#pragma once
#include <iostream>
#include "ObjectInfo.h"

using namespace sf;
using namespace std;

class Player : public ObjectInfo {
   // Movement components in x and y directions.
   float pMoveX, pMoveY;
   
public:
   float centerX, centerY;

   Player(int playerNum);
   
   void movement(float const &valX, float const &valY);

   void update(float& elapsedTime);
};