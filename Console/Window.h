#ifndef _Console__Window_h_
#define _Console__Window_h_

#include "../reu.h"
#include "Console.h"
#include "Util.h"



namespace Console {

class Window
{
	REU__PROPERTY(WINDOW*, window, Window);
	REU__PROPERTY(int, height, Height);
	REU__PROPERTY(int, width, Width);
	REU__PROPERTY(int, startY, StartY);
	REU__PROPERTY(int, startX, StartX);

public:
	typedef std::shared_ptr<Window> Ptr;

	Window(int h, int w, int y, int x);
	virtual ~Window();

	static Ptr create(int h, int w, int y, int x);
};

class WindowWorld : public Window
{
protected:
	static const int HEX_HEIGHT = 2;
	static const int HEX_WIDTH = 2;
	static const int HEX_SPACE = 2;

	// cursol position
	REU__PROPERTY(int, x, X);
	REU__PROPERTY(int, y, Y);
	REU__PROPERTY(int, worldHeight, WorldHeight);
	REU__PROPERTY(int, worldWidth, WorldWidth);
	REU__PROPERTY(bool, isWorldCylinder, IsWorldCylinder);

public:
	typedef std::shared_ptr<WindowWorld> Ptr;

	WindowWorld(int h, int w, int y, int x, int worldHeight, int worldWidth, bool isCylinder);
	virtual ~WindowWorld() {}
	static Ptr create(int h, int w, int y, int x, int wHeight, int wWidth, bool isCylinder);


	void moveLeft();
	void moveRight();
	void moveLeftUp();
	void moveRightUp();
	void moveRightDown();
	void moveLeftDown();

	void display(const World& world);

protected: 
	int getHexGridHeight();
	int getHexGridWidth();
};



//////////////////////////// Window.cpp ///////////////

char makeChLeftBottom(const Terrain& terrain);
	
//// Window class ////

Window::Window(int h, int w, int y, int x) :
	height(h),
	width(w),
	startY(y),
	startX(x)
{
	this->window = newwin(height, width, y, x);
}

Window::~Window()
{
	delwin(this->window);
}

Window::Ptr Window::create(int h, int w, int y, int x)
{
	return std::make_shared<Window>(h, w, y, x);
}

//// WindowWorld class ////

WindowWorld::WindowWorld(int h, int w, int y, int x, int worldHeight, int worldWidth, bool isCylinder) :
	Window(
			h > worldHeight ?
			worldHeight * HEX_HEIGHT :
			h * HEX_HEIGHT,

			w > worldWidth ?
			worldWidth * (HEX_WIDTH + HEX_SPACE) + HEX_SPACE :
			w * (HEX_WIDTH + HEX_SPACE) + HEX_SPACE, 

			y, x),
	x(worldWidth / 2),
	y(worldHeight / 2),
	worldHeight(worldHeight),
	worldWidth(worldWidth),
	isWorldCylinder(isCylinder)
{
	assert (h % 2 == 0);
	assert (w % 2 == 0);
}

WindowWorld::Ptr WindowWorld::create(int h, int w, int y, int x, int wHeight, int wWidth, bool isCylinder)
{
	return std::make_shared<WindowWorld>(h, w, y, x, wHeight, wWidth, isCylinder);
}

int WindowWorld::getHexGridHeight()
{
	return getHeight() / HEX_HEIGHT;
}

int WindowWorld::getHexGridWidth()
{
	return (getWidth() - HEX_SPACE) / (HEX_WIDTH + HEX_SPACE);
}

void WindowWorld::moveLeft() 
{
	x = Util::addCircle(x, -1, worldWidth - 1);
}
void WindowWorld::moveRight() 
{ 
	x = Util::addCircle(x, 1, worldWidth - 1);
}

void WindowWorld::moveLeftUp()
{
	y = Util::addCircle(y, -1, worldHeight - 1);

	if (y % 2 == 1) 
		x = Util::addCircle(x, -1, worldWidth - 1);
}

void WindowWorld::moveRightUp()
{
	y = Util::addCircle(y, -1, worldHeight - 1);

	if (y % 2 == 0) 
		x = Util::addCircle(x, 1, worldWidth - 1);
}

void WindowWorld::moveRightDown()
{
	y = Util::addCircle(y, 1, worldHeight - 1);

	if (y % 2 == 0) 
		x = Util::addCircle(x, 1, worldWidth - 1);

}

void WindowWorld::moveLeftDown()
{
	y = Util::addCircle(y, 1, worldHeight - 1);

	if (y % 2 == 1) 
		x = Util::addCircle(x, -1, worldWidth - 1);

}

void WindowWorld::display(const World& world)
{
	/* oo  oo
	 * oo  oo
	 *   oo  oo
	 *   oo  oo
	 * oo  oo
	 * oo  oo
	 *   oo  oo
	 *   oo  oo
	 */
	int isTargetEven = this->y % 2 == 0;

	for (int yy = 0; yy < getHeight(); yy++) {

		int relativeY = yy / HEX_HEIGHT - this->getHexGridHeight() / 2;
		int worldY = Util::addCircle(this->y, relativeY, world.height - 1);
		bool isEvenWorldY = worldY % 2 == 0;
		bool isThisEven = isTargetEven ? isEvenWorldY : ! isEvenWorldY;

		switch (yy % 4) {
		case 0:
		case 1:
			wmove (getWindow(), yy, 0);
			break;
		case 2:
		case 3:
			wmove (getWindow(), yy, HEX_SPACE);
			break;
		}

		for (int xx = 0; xx < this->getHexGridWidth(); xx++) {

			int xxx = isTargetEven ? xx : isThisEven ? xx : xx + 1;
			int worldX = Util::addCircle(this->x, xxx - this->getHexGridWidth() / 2, world.width - 1);
			auto terrain = world.terrains[worldY * world.width + worldX];

			switch (yy % HEX_HEIGHT) {
			case 0:
				// TODO
				//					waddch(getWindow, makeChUnit(terrain));
				waddch(getWindow(), ' ');
				break;
			case 1:
				waddch(getWindow(), makeChLeftBottom(terrain));
				waddch(getWindow(), ' ');
				break;
			default:
				assert(false);
			}

			waddch(getWindow(), ' ');
			waddch(getWindow(), ' ');



			//		waddch(getWindow, makeChLeftBottom(terrain) | COLOR_PAIR(color));

		}
	}

	wmove (getWindow(), 
			this->getHexGridHeight() - 3,
			(getWidth() - HEX_SPACE) / 2 - HEX_WIDTH - HEX_SPACE);
	wrefresh(getWindow());

	/*
	   for (int y = 0; y < world.height * 2; y++) {

	   switch (y % 4) {
	   case 0:
	   case 1:
	   wmove (getWindow, y, 0);
	   break;
	   case 2:
	   case 3:
	   wmove (getWindow, y, 2);
	   break;
	   }

	   for (int x = 0; x < world.width * 4; x++) {

	   auto terrain = world.terrains[y / 2 * world.width + x / 4];

	   switch (x % 4) {
	   case 0:
	   case 1: {
	   int color;

	   if (terrain.base == Terrain::BaseType::Coast
	   || terrain.base == Terrain::BaseType::Ocean) {
	   color = 3;
	   }
	   else if (terrain.feature == Terrain::FeatureType::Forest) {
	   color = 2;
	   }
	   else {
	   color = 1;
	   }

	   waddch(getWindow, makeChLeftBottom(terrain) | COLOR_PAIR(color));
	   }
	   break;
	   case 2:
	   case 3:
	   waddch(getWindow, ' ');
	   break;
	   }
	   }
	   }

	   wrefresh(getWindow);
	   */
}




char makeChLeftBottom(const Terrain& terrain)
{
	switch (terrain.base) {
	case Terrain::BaseType::None:
		return '+';
	case Terrain::BaseType::Glassland:
		if (terrain.vertical == Terrain::VerticalType::Flatland)
			return 'v';
		else
			return '-';

	case Terrain::BaseType::Plains:
		if (terrain.vertical == Terrain::VerticalType::Flatland)
			return '.';
		else
			return '^';

	case Terrain::BaseType::Tundra:
		if (terrain.vertical == Terrain::VerticalType::Flatland)
			return 't';
		else
			return 'T';

	case Terrain::BaseType::Desert:
		if (terrain.vertical == Terrain::VerticalType::Flatland)
			return 'd';
		else
			return 'D';

	case Terrain::BaseType::Ice:
		return '*';

		//// Oceans ////

	case Terrain::BaseType::Coast:
	case Terrain::BaseType::Ocean:
		return '~';
	default:
		return '?';
	}
}

} // end of namespace Console

#endif // _Console__Window_h_

