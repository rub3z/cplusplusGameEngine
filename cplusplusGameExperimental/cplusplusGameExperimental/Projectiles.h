#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <execution>
#include "ConstantsNStuff.h"
#include "GameObject.h"
#include "ObjectInfo.h"

using namespace sf;
using namespace std;
using namespace collision;

class Projectiles : public vector<ObjectInfo> {
   
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
   ObjectInfo & shootStraight(float& posX, float& posY, float& vX, float& vY);
   ObjectInfo & shootSpread(float& posX, float& posY, float& vX, float& vY);
   void collisionCheck(Sprite& other);
   void update(float & elapsedTime);
};