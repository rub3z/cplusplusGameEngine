#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <execution>
#include "GameObject.h"

class State : public sf::Drawable {
private:
   friend class State;
   std::vector<sf::Vertex> toDraw;
   std::vector<GameObject> previous;
   std::vector<GameObject * > current;
   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   int keepSize;

public:
   void clear();
   void interpolate(float alphaNum);
   void add(GameObject & o);
   void add(std::vector<GameObject> & vecInfo);
   void save();
   int size();
};