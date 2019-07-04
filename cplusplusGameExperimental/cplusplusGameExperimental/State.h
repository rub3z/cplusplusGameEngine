#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <execution>
#include "GameObject.h"
#include "ObjectInfo.h"


using namespace std;
using namespace sf;

class State : public Drawable {
private:
   friend class State;
   vector<Vertex> toDraw;
   vector<ObjectInfo> previous;
   vector<ObjectInfo * > current;
   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   int keepSize;

public:
   void clear();
   void interpolate(float alphaNum);
   void add(ObjectInfo & o);
   void add(vector<ObjectInfo> & vecInfo);
   void save();
   int size();
};