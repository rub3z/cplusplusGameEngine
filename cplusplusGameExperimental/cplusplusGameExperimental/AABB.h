#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "GameObject.h"

class AABB //: public sf::RectangleShape 
{
   friend class AABBTree;
private:
   float lowerBoundX;
   float lowerBoundY;
   float upperBoundX;
   float upperBoundY;

   int index;

   GameObject* objectPtr;
   
public:
   AABB() : lowerBoundX(), lowerBoundY(), upperBoundX(), upperBoundY() {}

   AABB(const float& lowerBoundX, const float& lowerBoundY,
        const float& upperBoundX, const float& upperBoundY);

   AABB(GameObject & objVertex);
   float getPerimeter();
   bool containsObject();
   bool objectCollisionRemoved();
   //void setDrawBounds();
};

inline float AABB::getPerimeter() {
   return ((upperBoundX - lowerBoundX) * 2.0f) 
        + ((upperBoundY - lowerBoundY) * 2.0f);
};

inline bool AABB::containsObject() {
   return objectPtr->posX > lowerBoundX &&
          objectPtr->posY > lowerBoundY &&
          objectPtr->posX + objectPtr->width  < upperBoundX &&
          objectPtr->posY + objectPtr->height < upperBoundY;
};

inline bool AABB::objectCollisionRemoved() {
   return !objectPtr->collideable;
}

//inline void AABB::setDrawBounds() {
//   this->setOutlineColor(sf::Color::Blue);
//   this->setOutlineThickness(2);
//   this->setFillColor(sf::Color::Transparent);
//   this->setPosition(lowerBoundX, lowerBoundY);
//   this->setSize(sf::Vector2f(upperBoundX - lowerBoundX,
//      upperBoundY - lowerBoundY));
//}