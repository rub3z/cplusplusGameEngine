#pragma once
#include "GameObject.h"

class Player : public GameObject {
   // Movement components in x and y directions.
   float pMoveX, pMoveY;

   void * vT[1];
   
public:
   float centerX, centerY;

   Player(int playerNum);
   
   void movement(float const &valX, float const &valY);

   void update(float& elapsedTime);

//   virtual void hit();

};