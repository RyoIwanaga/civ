#ifndef _Console__Window_h_
#define _Console__Window_h_

#include "Console.h"
#include "Util.h"

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
protected:
		static const int HEX_HEIGHT = 2;
		static const int HEX_WIDTH = 2;
		static const int HEX_SPACE = 2;

public:
	typedef std::shared_ptr<WindowWorld> Ptr;

	// cursol position
	int x, y;

	WindowWorld(int h, int w, int y, int x, int wHeight, int wWidth) :
		Window(h * HEX_HEIGHT, w * (HEX_WIDTH + HEX_SPACE) + HEX_SPACE, y, x),
		x(wWidth / 2),
		y(wHeight / 2)
	{
		assert (h % 2 == 0);
		assert (w % 2 == 0);
	}

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
		 *   oo  oo
		 *   oo  oo
		 */
		int windowMiddleY = this->height / 2;
		int windowMiddleX = this->width / 2;
		int isTargetEven = this->y % 2 == 0;


		for (int yy = 0; yy < this->height; yy++) {

			int relativeY = yy / HEX_HEIGHT - windowMiddleY;
			int worldY = Util::addCircle(this->y, relativeY, world.height - 1);
			bool isEvenWorldY = worldY % 2 == 0;
			bool isThisEven = isTargetEven ? isEvenWorldY : ! isEvenWorldY;

			switch (yy % 4) {
			case 0:
			case 1:
				wmove (window, yy, 0);
				break;
			case 2:
			case 3:
				wmove (window, yy, HEX_SPACE);
				break;
			}

			for (int xx = 0; xx < (this->width - HEX_SPACE) / (HEX_WIDTH + HEX_WIDTH); xx++) {

				int xxx = isTargetEven ? xx : isThisEven ? xx : xx + 1;
				int worldX = Util::addCircle(this->x, xxx - windowMiddleX, world.width - 1);
				auto terrain = world.terrains[worldY * world.width + worldX];

				waddch(this->window, 'a');
				waddch(this->window, 'a');
				waddch(this->window, ' ');
				waddch(this->window, ' ');

				

				//		waddch(window, makeChLeftBottom(terrain) | COLOR_PAIR(color));

			}
		}

		wmove (window, 
				this->height / 2 - HEX_HEIGHT, 
				(this->width - HEX_SPACE) / 2 - HEX_WIDTH - HEX_SPACE);
		wrefresh(this->window);

		/*
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
	*/
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

