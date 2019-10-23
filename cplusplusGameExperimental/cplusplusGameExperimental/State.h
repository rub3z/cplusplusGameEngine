#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <execution>
#include "ObjectInfo.h"

class State : public sf::Drawable {
private:
   friend class State;
   std::vector<sf::Vertex> toDraw;
   std::vector<ObjectInfo> previous;
   std::vector<ObjectInfo * > current;
   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   int keepSize;

public:
   void clear();
   void interpolate(float alphaNum);
   void add(ObjectInfo & o);
   void add(std::vector<ObjectInfo> & vecInfo);
   void save();
   int size();
};