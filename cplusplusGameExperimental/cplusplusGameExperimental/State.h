#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;
using namespace sf;

class State : public Drawable {
private:
   //friend class RenderTarget;
   friend class State;
   vector<Sprite> sprites;
   //friend void Engine::update(float& dtAsSeconds);
   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
   
   //State operator=(State otherState);
   void clear();
   void add(Sprite s);
   State operator*(float alphaNum);
   State operator+(State otherState);
};