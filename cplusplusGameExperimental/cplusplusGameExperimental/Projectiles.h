#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <execution>
#include "GameObject.h"
#include "ObjectInfo.h"

using namespace sf;
using namespace std;
 
class Projectiles : public vector<ObjectInfo> {
   
   int pIterator;
   float width, height;

private:
   struct Info {
      int index;
      float distanceX, distanceY;
      float moveX, moveY;
      float pAccX, pAccY;
      float distance;
      float lifetime;
      bool shot;
   };

   std::vector<Info> info;
   
public:
   Projectiles();
   ObjectInfo & shootStraight(float& posX, float& posY, const float& vX, const float& vY);
   ObjectInfo & shootSpread(float& posX, float& posY, float& vX, float& vY);
   void collisionCheck(Sprite& other);
   void update(float & elapsedTime);
};