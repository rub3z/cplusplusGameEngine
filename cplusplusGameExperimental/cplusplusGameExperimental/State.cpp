#include "stdafx.h"
#include "State.h"


void State::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
   for (Sprite s : sprites) {
      target.draw(s);
   }
}

void State::clear() {
   sprites.clear();
}

void State::add(Sprite s)
{
   sprites.push_back(s);
}

State State::operator*(float alphaNum)
{
   State temp(*this);
   for (int i = 0; i < temp.sprites.size(); i++) {
      temp.sprites.at(i).setPosition(temp.sprites.at(i).getPosition() * alphaNum);
   }
   return temp;
}

State State::operator+(State otherState)
{
   State temp(*this);
   for (int i = 0; i < temp.sprites.size(); i++) {
      temp.sprites.at(i).move(otherState.sprites.at(i).getPosition());
   }
   return temp;
}
