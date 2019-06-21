#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <execution>
#include "GameObject.h"
#include "VertexInfo.h"


using namespace std;
using namespace sf;

class State : public Drawable {
private:
   friend class State;
   vector<Vertex> toDraw;
   vector<VertexInfo> previous;
   vector<VertexInfo * > current;
   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   int keepSize;

public:
   void clear();
   void interpolate(float alphaNum);
   void add(vector<VertexInfo> & vecInfo);
   void save();
   int size();
};