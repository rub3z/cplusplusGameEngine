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
   centerX = objectPtr->posX + (objectPtr->width/2);
   centerY = objectPtr->posY - (objectPtr->height/2);
   radiusX = (objectPtr->width / 2) + (objectPtr->width * 0.2f);
   radiusY = (objectPtr->height / 2) + (objectPtr->width * 0.2f);
   //this->setOutlineColor(Color::Blue);
   //this->setOutlineThickness(2);
   //this->setFillColor(Color::Transparent);
   //this->setPosition(objectPtr->posX - 5, objectPtr->posY - 5);
   //this->setSize(Vector2f(objectPtr->width + 10, objectPtr->height + 10));
}

