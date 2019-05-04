#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;
using namespace sf;

class State : public Drawable {
private:
   friend class State;
   vector<Sprite> sprites;
   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
   void clear();
   void add(Sprite s);
   State operator*(float alphaNum);
   State operator+(State otherState);
};