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

AABB::AABB(GameObject & obj) {
   objectPtr = &obj;
   centerX = objectPtr->posX + (objectPtr->width/2);
   centerY = objectPtr->posY + (objectPtr->height/2);
   radiusX = (objectPtr->width / 2) + 2;
   radiusY = (objectPtr->height / 2) + 2;
   //this->setOutlineColor(Color::Blue);
   //this->setOutlineThickness(2);
   //this->setFillColor(Color::Transparent);
   //this->setPosition(objectPtr->posX - 2, objectPtr->posY - 2);
   //this->setSize(Vector2f(objectPtr->width + 4, objectPtr->height + 4));
}

