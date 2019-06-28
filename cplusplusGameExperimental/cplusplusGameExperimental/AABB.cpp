#include "stdafx.h"
#include "AABB.h"

AABB::AABB(VertexInfo & objVertex) {
   obj = &objVertex;
   this->setOutlineColor(Color::Blue);
   this->setOutlineThickness(2);
   this->setFillColor(Color::Transparent);
   this->setPosition(obj->posX - 5, obj->posY - 5);
   this->setSize(
      Vector2f(obj[1].posX - obj[0].posX + 10,
               obj[3].posY - obj[0].posY + 10));
   centerX = this->getPosition().x + (this->getSize().x / 2);
   centerY = this->getPosition().y + (this->getSize().y / 2);
   radiusX = this->getSize().x / 2;
   radiusY = this->getSize().y / 2;
}

void AABB::update()
{
   this->setPosition(obj->posX - 5, obj->posY - 5);
   centerX = this->getPosition().x + (this->getSize().x / 2);
   centerY = this->getPosition().y + (this->getSize().y / 2);
}
