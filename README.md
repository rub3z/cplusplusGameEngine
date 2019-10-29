# C++ Game Engine Project
Experimenting with OO vs. Data-Oriented design; Broadphase Collision; Runtime Polymorphism; and maybe some other things.

## Setting Up
To run this and see it actually work; follow this tutorial to set up SFML in Visual Studio:
http://gamecodeschool.com/sfml/building-your-first-sfml-game-project/

SFML is really great for starting off in C++ game code; as it provides you with tools that will make a window for your game that you can draw stuff in; and methods for taking in input from a keyboard or joystick... things that just *work*.

## Highlights

### 1. Achieving variable framerate.

  Related files: [Engine.cpp](./Engine.cpp) [State.cpp](./State.cpp) [Input.cpp](./Input.cpp) [Update.cpp](./Update.cpp) [Draw.cpp](./Draw.cpp) [Engine.h](./Engine.h) [State.h](./State.h)
  
  I learned about the idea of doing this from Glenn Fiedler's legendary piece on it which *would be* on gafferongames.com... but unfortunately it seems to have been shut down. Fortunately, it's archived here! http://vodacek.zvb.cz/archiv/681.html
  
I highly recommend it for anyone trying to make a game or game engine completely from scratch. I would even say it is essential.

### 2. Broadphase collision using an AABBTree (binary tree) data structure.

  Related files: [AABBTree.cpp](./AABBTree.cpp) [AABB.cpp](./AABB.cpp) [AABBTree.h](./AABBTree.h) [AABB.h](./AABB.h) 
  
  There are tons of resources and articles on this you can find by googling AABBTree or broadphase collision; but I'll list the best ones I've found...
  
  This guide by James Randall is a great place to start, going through the basic logic of how an AABBTree works, step-by-step:
  
  https://www.azurefromthetrenches.com/introductory-guide-to-aabb-tree-collision-detection/
  
  This is the next place I'd go (the previous article has a link to it at the bottom); as Randy Gaul provides descriptions of the functions you would have to write and shows very simple examples of code snippets you would probably want to use in your own implementation (it's not the entire implementation, mind... you can't just copy-paste stuff from here and expect it to work):
  
  https://www.randygaul.net/2013/08/06/dynamic-aabb-tree/
  
  And finally, when you want a deep-dive; to *really* get down to business with understanding how to write AABBTree code and what it looks like; look at Erin Catto's Box2D and Nathanael Presson's Dynamic Bounding Volume Tree code in Bullet:
  
  https://github.com/erincatto/Box2D/tree/master/Box2D/Collision *look at Broadphase and DynamicTree files*
  
  https://github.com/bulletphysics/bullet3/tree/master/src/BulletCollision/BroadphaseCollision *look at Dbvt and DbvtBroadphase files*
  
  You may also want to look at James Randall and Lester Hedge's own implementation(s) of these algorithms; useful to get more insight on how they work if you're looking through the code in Box2D or Bullet and thinking "OMG, just what the heck is going on in these functions, I can't read this stuff"; as they use different variable and function names that may prove easier for you to understand:
  
  https://github.com/JamesRandall/SimpleVoxelEngine/blob/master/voxelEngine/src/AABBTree.cpp
  
  https://github.com/lohedges/aabbcc/tree/master/src
  
### 3. Runtime Polymorphism Using Double Indirection / Function Pointers for Generic Game Objects.

  Related files: [GameObject.h](./GameObject.h) [Enemies.cpp](./Enemies.cpp) [Player.cpp](./Player.cpp) [Projectiles.cpp](./Projectiles.cpp)
  
  This is something I actually came up with myself. Kind of a mouthful, isn't it? I'm not sure how to put it, exactly. I'll explain this later (:
