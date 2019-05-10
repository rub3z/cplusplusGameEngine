#include "stdafx.h"
#include "State.h"


void State::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
   for (Sprite s : previous) {
      target.draw(s);
   }
}

void State::clear() {
   current.clear();
}

void State::add(Sprite * s)
{
   current.push_back(s);
   previous.push_back(*s);
   keepSize = current.size();
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
   for (int i = 0; i < previous.size(); i++) {
      previous.at(i).setPosition(
         (current.at(i)->getPosition() * alphaNum) +
         (previous.at(i).getPosition() * (1.0f - alphaNum)));
   }
}

void State::interpolateI(float alphaNum, int begin, int end)
{
   for (int i = begin; i < end; i++) {
      previous.at(i).setPosition(
         (current.at(i)->getPosition() * alphaNum) +
         (previous.at(i).getPosition() * (1.0f - alphaNum)));
   }
}
