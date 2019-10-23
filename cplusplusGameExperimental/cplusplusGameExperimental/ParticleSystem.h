// Adapted from code used in this tutorial:
// https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php
#pragma once
#include "stdafx.h"
#include <execution>

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
   int enemyType;
   
public:

   ParticleSystem::ParticleSystem();
   void update(float& elapsedTime, float& playerPosX, float& playerPosY);

private:
   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
   
   struct Info {
      int index;
      float distanceX, distanceY;
      float pAccX, pAccY;
      float distance;
   };
   
   std::vector<Info> quadInfo;
   std::vector<sf::Vertex> vertices;
};