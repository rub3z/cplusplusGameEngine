// Adapted from code used in this tutorial:
// https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php
#pragma once
#include "stdafx.h"
#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
   vertices.assign(MAX_ENEMY1 * 4, sf::Vertex(sf::Vector2f(0, 0), sf::Color::Red));
   quadInfo.resize(MAX_ENEMY1);

   for (int i = 0; i < MAX_ENEMY1; i++) {
      quadInfo[i].index = i * 4;
   }
}

void ParticleSystem::update(float& elapsedTime, float& playerPosX, float& playerPosY)
{
   transform(std::execution::par_unseq,
      quadInfo.begin(), quadInfo.end(),
      quadInfo.begin(), [&](Info i) {
         sf::Vertex* quad = &vertices[i.index];

         i.distanceX = playerPosX - quad[0].position.x;
         i.distanceY = playerPosY - quad[0].position.y;
         i.distance = sqrt(pow(i.distanceX, 2) + pow(i.distanceY, 2));

         quad[0].position.x += (ENEMY1_SPEED / i.distance) * (i.distanceX)* elapsedTime;
         quad[1].position.x += (ENEMY1_SPEED / i.distance) * (i.distanceX)* elapsedTime;
         quad[2].position.x += (ENEMY1_SPEED / i.distance) * (i.distanceX)* elapsedTime;
         quad[3].position.x += (ENEMY1_SPEED / i.distance) * (i.distanceX)* elapsedTime;

         quad[0].position.y += (ENEMY1_SPEED / i.distance) * (i.distanceY)* elapsedTime;
         quad[1].position.y += (ENEMY1_SPEED / i.distance) * (i.distanceY)* elapsedTime;
         quad[2].position.y += (ENEMY1_SPEED / i.distance) * (i.distanceY)* elapsedTime;
         quad[3].position.y += (ENEMY1_SPEED / i.distance) * (i.distanceY)* elapsedTime;

         return i;
      });
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   // apply the transform
   //states.transform *= getTransform();

   // draw the vertex array
   target.draw(&vertices[0], vertices.size(), sf::Quads);
}
