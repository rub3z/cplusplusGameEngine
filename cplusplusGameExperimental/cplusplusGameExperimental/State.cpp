#include "stdafx.h"
#include "State.h"


void State::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
   for (GameObject s : previous) {
      target.draw(s);
   }
}

void State::clear() {
   current.clear();
}

void State::add(GameObject * s)
{
   current.push_back(s);
   previous.push_back(*s);
   keepSize = current.size();
}

void State::save() {
   //*previous.data() = **current.data();
   for (int i = 0; i < keepSize; i++) {
      previous[i] = *current[i];
   }
}

int State::size()
{
   return current.size();
}

void State::interpolate(float alphaNum)
{
   for (int i = 0; i < previous.size(); i++) {
      previous.at(i).setPosition(
         (current.at(i)->posX * alphaNum) +
         (previous.at(i).posX * (1.0f - alphaNum)),
         (current.at(i)->posY * alphaNum) +
         (previous.at(i).posY * (1.0f - alphaNum)));
   }
}

//void State::interpolateI(float alphaNum, int begin, int end)
//{
//   for (int i = begin; i < end; i++) {
//      previous.at(i).setPosition(
//         (current.at(i)->getPosition() * alphaNum) +
//         (previous.at(i).getPosition() * (1.0f - alphaNum)));
//   }
//}
