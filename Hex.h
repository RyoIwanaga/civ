#ifndef _Hex_h_
#define _Hex_h_

#include <list>

#include <stdio.h>

class Hex
{
public:
	static std::list<int> neighbors(int index, int height, int width, bool isCyinder)
	{
		/*  width = 3
		 *
		 *     0 1 2
		 *	 +-------
		 * 0 | 0 1 2
		 * 1 |  3 4 5
		 * 2 | 6 7 8
		 * 3 |  9 a b 
		 */
		int y = index / width;
		int x = index % width; 
		std::list<int> lst;

		//// left ////

		// 3 -> 5 
		if (x == 0 && isCyinder) {
			lst.push_back(index + width - 1);	
		}
		// 3 
		else if (x == 0 && ! isCyinder) {
			// pass
		}
		// 4 -> 3
		else {
			lst.push_back(index - 1);	
		}


		//// right ////

		// 5 -> 3
		if (x == width - 1 && isCyinder) {
			lst.push_back(index - width + 1);	
		}
		// 5
		else if (x == width - 1 && ! isCyinder) {
			// pass
		}
		// 4 -> 5
		else {
			lst.push_back(index + 1);	
		}


		if (y > 0) {

			// odd y
			if (y % 2 == 0) {

				//// upper left ////

				// 6 -> 5
				if (x == 0 && isCyinder) {
					lst.push_back(index - 1);	
				}
				// 6
				else if (x == 0 && ! isCyinder) {
					// pass
				}
				// 7 -> 3
				else {
					lst.push_back(index - width - 1);	
				}

				//// upper right ////

				// 8 -> 5
				lst.push_back(index - width);	
			}
			// y is even
			else {
				//// upper left ////

				// 3 -> 0
				lst.push_back(index - width);


				//// upper right ////

				// 5 -> 0
				if (x == width - 1 && isCyinder) {
					lst.push_back(index - width * 2 + 1);	
				}
				// 5
				else if (x == width - 1 && ! isCyinder) {
					// pass
				}
				// 4 -> 3
				else {
					lst.push_back(index - width + 1);	
				}
			}
		}

		if (y < height - 1) {

			// y == 0 or 2
			if (y % 2 == 0) {

				//// left lower ////

				// 6 -> 11 
				if (x == 0 && isCyinder) {
					lst.push_back(index + width * 2 - 1);	
				}
				// 6
				else if (x == 0 && ! isCyinder) {
					// pass
				}
				// 7 -> 9
				else {
					lst.push_back(index + width - 1);	
				}

				//// right lower ////

				// 8 -> 11
				lst.push_back(index + width);	
			}
			else {
				//// left lower ////

				// 3 -> 6
				lst.push_back(index + width);


				//// right lower ////

				// 5 -> 6
				if (x == width - 1 && isCyinder) {
					lst.push_back(index + 1);	
				}
				// 5
				else if (x == width - 1 && ! isCyinder) {
					// pass
				}
				// 4 -> 8
				else {
					lst.push_back(index + width + 1);	
				}
			}
		}

		return lst;
	}
};

#endif // _Hex_h_

