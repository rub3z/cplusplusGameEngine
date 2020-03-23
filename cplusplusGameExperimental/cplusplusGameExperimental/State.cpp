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
   o.drawIndex = current.size() * 4;
   current.push_back(&o);
   previous.push_back(o);
   toDraw.push_back(sf::Vertex(sf::Vector2f(o.posX, o.posY)));
   toDraw.push_back(sf::Vertex(sf::Vector2f(o.posX + o.width, o.posY)));
   toDraw.push_back(sf::Vertex(sf::Vector2f(o.posX + o.width, o.posY + o.height)));
   toDraw.push_back(sf::Vertex(sf::Vector2f(o.posX, o.posY + o.height)));

}

void State::add(std::vector<GameObject> & v)
{
   for (size_t i = 0; i < v.size(); i++) {
      v[i].drawIndex = current.size() * 4;
      current.push_back(&v[i]);
      previous.push_back(v[i]);
      toDraw.push_back(sf::Vertex(sf::Vector2f(v[i].posX, v[i].posY)));
      toDraw.push_back(sf::Vertex(sf::Vector2f(v[i].posX + v[i].width, v[i].posY)));
      toDraw.push_back(sf::Vertex(sf::Vector2f(v[i].posX + v[i].width, v[i].posY + v[i].height)));
      toDraw.push_back(sf::Vertex(sf::Vector2f(v[i].posX, v[i].posY + v[i].height)));

      keepSize = current.size();
   }
}

void State::save() {
   transform(std::execution::par,
      previous.begin(), previous.end(),
      current.begin(), previous.begin(),
      [&](GameObject p, GameObject* c) {
         p = *c;
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
      [&](GameObject p, GameObject* c) {
         p.posX = (c->posX * alphaNum) +
            (p.posX * (1.0f - alphaNum));
         p.posY = (c->posY * alphaNum) +
            (p.posY * (1.0f - alphaNum));
         p.r = c->r; p.g = c->g; p.b = c->b;

         return p;
      });

   transform(std::execution::par,
      previous.begin(), previous.end(),
      previous.begin(), [&](GameObject p) {
         sf::Vertex* quad = &toDraw[p.drawIndex];

         quad[0].position.x = p.posX;
         quad[0].position.y = p.posY;
         quad[0].color.r = p.r; quad[0].color.g = p.g; quad[0].color.b = p.b;

         quad[1].position.x = p.posX + p.width;
         quad[1].position.y = p.posY;
         quad[1].color.r = p.r; quad[1].color.g = p.g; quad[1].color.b = p.b;

         quad[2].position.x = p.posX + p.width;
         quad[2].position.y = p.posY + p.height;
         quad[2].color.r = p.r; quad[2].color.g = p.g; quad[2].color.b = p.b;

         quad[3].position.x = p.posX;
         quad[3].position.y = p.posY + p.height;
         quad[3].color.r = p.r; quad[3].color.g = p.g; quad[3].color.b = p.b;

         return p;
      });
}
