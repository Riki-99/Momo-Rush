#pragma once
#include "loader.h"
#include "map.h"

class Traps : virtual public Tile{
protected:
public:
	Traps() : Element(0, 0, 0, 0, 0, tiletxtr) { frameCt = 0;}
};

class bearTrap : public Traps {
public:
	bearTrap(int wth, int ht, int fct) : Element(0, 0, 0, wth, ht, TextureList<bearTrap>::getTexture(0)), Tile(0, 0, 0, wth, ht, 5, fct){
		frameCt = fct;
	}
};
class fireTrap : public Traps {
public:
	fireTrap(int wth, int ht, int fct) : Element(0, 0, 0, wth, ht, TextureList<fireTrap>::getTexture(0)), Tile(0, 0, 0, wth, ht, 6, fct) {
		frameCt = fct;
	}
};
class pitTrap : public Traps {
public:
	pitTrap(int wth, int ht, int fct) : Element(0, 0, 0, wth, ht, TextureList<pitTrap>::getTexture(0)), Tile(0, 0, 0, wth, ht, 7, fct) {
		frameCt = fct;
	}
};
class spikeTrap : public Traps {
public:
	spikeTrap(int wth, int ht, int fct) : Element(0, 0, 0, wth, ht, TextureList<spikeTrap>::getTexture(0)), Tile(0, 0, 0, wth, ht, 8, fct) {
		frameCt = fct;
	}
};

class momoTrap : public Traps {
public:
	momoTrap(int wth, int ht, int fct) : Element(0, 0, 0, wth, ht, TextureList<momoTrap>::getTexture(0)), Tile(0, 0, 0, wth, ht, 4, fct) {
		frameCt = fct;
		sprite.scale({0.4f, 0.4f});
	}
};