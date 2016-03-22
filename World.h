#ifndef _World_h_
#define _World_h_

#include <memory>
#include <vector>

#include "Terrain.h"

class World
{
public:
	typedef std::shared_ptr<World> Ptr;

	int height;
	int width;
	bool isCylinder;

	std::vector<Terrain> terrains;

	World (int height, int width, bool isCylinder) :
		height(height),
		width(width),
		isCylinder(isCylinder)
	{}

	static Ptr createMassive(int height, int width, bool isCylinder, float landPersentage);
};

class Pos
{
public:
	int x, y;

	Pos(int x, int y) :
		x(x),
		y(y)
	{}
};

#endif // _World_h_

