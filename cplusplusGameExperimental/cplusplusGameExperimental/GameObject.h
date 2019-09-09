#pragma once
#include <vector>

class GameObject : public sf::Sprite {
   friend class State;
public:
   float posX, posY;
};