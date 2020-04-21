#include "stdafx.h"
#include "State.h"


void State::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
   target.draw(&toDraw[0], toDraw.size(), sf::Quads, states);
}

void State::clear() {
   current.clear();
}

void State::add(GameObject & o)
{
   previous.emplace_back(current.size() * 4, o);
   current.push_back(&o);
   toDraw.emplace_back();
   toDraw.emplace_back();
   toDraw.emplace_back();
   toDraw.emplace_back();
}

void State::add(std::vector<GameObject> & v)
{
   for (size_t i = 0; i < v.size(); i++) {
      previous.emplace_back(current.size() * 4, v[i]);
      current.push_back(&v[i]);
      toDraw.emplace_back();
      toDraw.emplace_back();
      toDraw.emplace_back();
      toDraw.emplace_back();
   }
}

void State::save() {
   transform(std::execution::par,
      previous.begin(), previous.end(),
      current.begin(), previous.begin(),
      [&](DrawObject p, GameObject* c) {
         p.obj = *c;
         return p;
      });
}

int State::size()
{
   return current.size();
}

void State::interpolate(float alphaNum)
{
   transform(std::execution::par,
      previous.begin(), previous.end(),
      current.begin(), previous.begin(),
      [&](DrawObject p, GameObject* c) {
         p.obj.posX = (c->posX * alphaNum) +
            (p.obj.posX * (1.0f - alphaNum));
         p.obj.posY = (c->posY * alphaNum) +
            (p.obj.posY * (1.0f - alphaNum));
         p.obj.r = c->r; p.obj.g = c->g; p.obj.b = c->b;

         return p;
      });

   transform(std::execution::par,
      previous.begin(), previous.end(),
      previous.begin(), [&](DrawObject p) {
         sf::Vertex* quad = &toDraw[p.drawIndex];

         quad[0].position.x = p.obj.posX;
         quad[0].position.y = p.obj.posY;
         quad[0].color.r = p.obj.r; 
         quad[0].color.g = p.obj.g; 
         quad[0].color.b = p.obj.b;

         quad[1].position.x = p.obj.posX + p.obj.width;
         quad[1].position.y = p.obj.posY;
         quad[1].color.r = p.obj.r; 
         quad[1].color.g = p.obj.g; 
         quad[1].color.b = p.obj.b;

         quad[2].position.x = p.obj.posX + p.obj.width;
         quad[2].position.y = p.obj.posY + p.obj.height;
         quad[2].color.r = p.obj.r; 
         quad[2].color.g = p.obj.g; 
         quad[2].color.b = p.obj.b;

         quad[3].position.x = p.obj.posX;
         quad[3].position.y = p.obj.posY + p.obj.height;
         quad[3].color.r = p.obj.r; 
         quad[3].color.g = p.obj.g; 
         quad[3].color.b = p.obj.b;

         return p;
      });
}
