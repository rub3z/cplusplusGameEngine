#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <execution>
#include "ConstantsNStuff.h"
#include "RectangularBoundaryCollision.h"
#include "GameObject.h"
#include "VertexInfo.h"

using namespace sf;
using namespace std;
using namespace collision;

class Projectiles : public vector<VertexInfo> {
   
   int pIterator;
   int width, height;

private:
   struct Info {
      int index;
      float distanceX, distanceY;
      float moveX, moveY;
      float pAccX, pAccY;
      float distance;
      float lifetime;
   };

   std::vector<Info> quadInfo;
   
public:
   Projectiles();
   void shootStraight(float& posX, float& posY, float& vX, float& vY);
   void shootSpread(float& posX, float& posY, float& vX, float& vY);
   void collisionCheck(Sprite& other);
   void update(float & elapsedTime);
};