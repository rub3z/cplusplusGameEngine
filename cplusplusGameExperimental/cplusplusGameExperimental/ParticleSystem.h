// Adapted from code used in this tutorial:
// https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php
#pragma once
#include "stdafx.h"
#include <execution>

using namespace sf;

class ParticleSystem : public Drawable, public Transformable
{
   int enemyType;
   
public:

   ParticleSystem::ParticleSystem();
   void update(float& elapsedTime, float& playerPosX, float& playerPosY);

private:
   virtual void draw(RenderTarget& target, RenderStates states) const;
   
   struct Info {
      int index;
      float distanceX, distanceY;
      float pAccX, pAccY;
      float distance;
   };
   
   std::vector<Info> quadInfo;
   std::vector<Vertex> vertices;
};