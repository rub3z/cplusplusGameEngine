#include "stdafx.h"
#include "AABB.h"



AABB::AABB(const float& cX, const float& cY, const float& rX, const float& rY)
{
   centerX = cX; centerY = cY; radiusX = rX; radiusY = rY;
   objectPtr = NULL;
   //this->setOutlineColor(Color::Blue);
   //this->setOutlineThickness(2);
   //this->setFillColor(Color::Transparent);
   //this->setPosition(centerX - radiusX, centerY - radiusY);
   //this->setSize(Vector2f(radiusX * 2.0f, radiusY * 2.0f));
}

AABB::AABB(ObjectInfo & obj) {
   objectPtr = &obj;
   centerX = objectPtr->posX - 5;
   centerY = objectPtr->posY - 5;
   radiusX = objectPtr->width + 5;
   radiusY = objectPtr->height + 5;
   //this->setOutlineColor(Color::Blue);
   //this->setOutlineThickness(2);
   //this->setFillColor(Color::Transparent);
   //this->setPosition(centerX, centerY);
   //this->setSize(Vector2f(objectPtr->width + 10, objectPtr->height + 10));
}

