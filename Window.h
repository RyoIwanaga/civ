#ifndef _Console__Window_h_
#define _Console__Window_h_

#include "Console.h"

namespace Console {

char makeChLeftBottom(const Terrain& terrain);
	
class Window
{
public:
	typedef std::shared_ptr<Window> Ptr;

	WINDOW* window;
	int height;
	int width;
	int startY;
	int startX;

	Window(int h, int w, int y, int x) :
		height(h),
		width(w),
		startY(y),
		startX(x)
	{
		window = newwin(height, width, y, x);
	}

	~Window()
	{
		delwin(window);
	}

	static Ptr create(int h, int w, int y, int x)
	{
		return std::make_shared<Window>(h, w, y, x);
	}
};

class WindowWorld : public Window
{
public:
	typedef std::shared_ptr<WindowWorld> Ptr;

	int worldHeight;
	int worldWidth;
	int x, y;

	WindowWorld(int h, int w, int y, int x, int wHeight, int wWidth) :
		Window(h, w, y, x),
		worldHeight(wHeight),
		worldWidth(wWidth),
		x(wWidth / 2),
		y(wHeight / 2)
	{}

	static Ptr create(int h, int w, int y, int x, int wHeight, int wWidth)
	{
		return std::make_shared<WindowWorld>(h, w, y, x, wHeight, wWidth);
	}

	void display(const World& world)
	{
		/* oo  oo
		 * oo  oo
		 *   oo  oo
		 *   oo  oo
		 * oo  oo
		 * oo  oo
		 */
		for (int y = 0; y < world.height * 2; y++) {

			switch (y % 4) {
			case 0:
			case 1:
				wmove (window, y, 0);
				break;
			case 2:
			case 3:
				wmove (window, y, 2);
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

							waddch(window, makeChLeftBottom(terrain) | COLOR_PAIR(color));
						}
						break;
				case 2:
				case 3:
						waddch(window, ' ');
						break;
				}
			}
		}

		wrefresh(window);
	}
};


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

