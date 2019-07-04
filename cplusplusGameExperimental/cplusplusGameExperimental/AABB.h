#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "ObjectInfo.h"

using namespace sf;
using namespace std;

class AABB : public RectangleShape {
   friend class AABBTree;
private:
   float centerX;
   float centerY;
   float radiusX;
   float radiusY;

   ObjectInfo* objectPtr;
   
public:
   AABB() : centerX(), centerY(), radiusX(), radiusY() {}

   AABB(const float& cX, const float& cY,
      const float& rX, const float& rY);
   AABB(ObjectInfo & objVertex);
   float getPerimeter();
   void update();
   bool objectCollisionRemoved();
};

inline float AABB::getPerimeter() {
   return (radiusX * 4.0f) + (radiusY * 4.0f);
};

inline void AABB::update() {
   centerX = objectPtr->posX - 5 + radiusX;
   centerY = objectPtr->posY - 5 + radiusY;
   //this->setPosition(objectPtr->posX - 5, objectPtr->posY - 5);
};

inline bool AABB::objectCollisionRemoved() {
   return objectPtr->collisionIndex == -1;
}