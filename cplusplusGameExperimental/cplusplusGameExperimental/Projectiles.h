#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <execution>
#include "GameObject.h"

struct BulletInfo {
   int index;
   float moveX, moveY;
   float pAccX, pAccY;
   float lifetime;
   bool shot;
   bool flag;
};

class Projectiles : public std::vector<GameObject> {
   size_t pIterator;
   float width, height;

private:
   
   std::vector<BulletInfo> info;
   void* vT[3];
   
public:
   Projectiles();
   void shoot(float& posX, float& posY, const float& vX, const float& vY, 
      bool type, float & fireRateDelta);
   void update(float & elapsedTime);
   std::vector<GameObject*> flagged;
};