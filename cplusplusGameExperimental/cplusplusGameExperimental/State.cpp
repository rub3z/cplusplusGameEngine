#include "stdafx.h"
#include "State.h"


void State::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
   target.draw(&toDraw[0], toDraw.size(), Quads, states);
}

void State::clear() {
   current.clear();
}

void State::add(vector<VertexInfo> & v)
{
   for (int i = 0; i < v.size(); i++) {
      current.push_back(&v[i]);
      previous.push_back(v[i]);
      toDraw.push_back(Vertex(sf::Vector2f(v[i].posX, v[i].posX), 
         Color::Color(v[i].r, v[i].g, v[i].b, 255)));
      keepSize = current.size();
   }
}

void State::save() {
   *previous.data() = **current.data();
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
      [&](VertexInfo p, VertexInfo* c) {
         p.posX = (c->posX * alphaNum) +
            (p.posX * (1.0f - alphaNum));
         p.posY = (c->posY * alphaNum) +
            (p.posY * (1.0f - alphaNum));
         p.r = c->r;
         p.g = c->g;
         p.b = c->b;

         return p;
      });

   transform(std::execution::par,
      toDraw.begin(), toDraw.end(),
      previous.begin(), toDraw.begin(),
      [&](Vertex v, VertexInfo p) {
         v.position.x = p.posX;
         v.position.y = p.posY;
         v.color.r = p.r;
         v.color.g = p.g;
         v.color.b = p.b;
         return v;
      });

}