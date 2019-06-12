#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class GameObject : public sf::Sprite {
   friend class State;
public:
   float posX, posY;
};