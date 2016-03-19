#include "../Hex.h"
#include <iostream>

void printHex(int index, const std::list<int>& lst)
{
	std::cout << index << ": ";

	for (auto item: lst) {
		std::cout << item << ", ";
	}

	std::cout << std::endl;
}

int main(void)
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

	const int height = 4;
	const int width = 3;

	printHex(0, Hex::neighbors(0, height, width, false));
	printHex(1, Hex::neighbors(1, height, width, false));
	printHex(2, Hex::neighbors(2, height, width, false));
	printHex(3, Hex::neighbors(3, height, width, false));
	printHex(4, Hex::neighbors(4, height, width, false));
	printHex(5, Hex::neighbors(5, height, width, false));
	printHex(6, Hex::neighbors(6, height, width, false));
	printHex(7, Hex::neighbors(7, height, width, false));
	printHex(8, Hex::neighbors(8, height, width, false));
	printHex(9, Hex::neighbors(9, height, width, false));
	printHex(10, Hex::neighbors(10, height, width, false));
	printHex(11, Hex::neighbors(11, height, width, false));
	std::cout << std::endl;

	printHex(0, Hex::neighbors(0, height, width, true));
	printHex(1, Hex::neighbors(1, height, width, true));
	printHex(2, Hex::neighbors(2, height, width, true));
	printHex(3, Hex::neighbors(3, height, width, true));
	printHex(4, Hex::neighbors(4, height, width, true));
	printHex(5, Hex::neighbors(5, height, width, true));
	printHex(6, Hex::neighbors(6, height, width, true));
	printHex(7, Hex::neighbors(7, height, width, true));
	printHex(8, Hex::neighbors(8, height, width, true));
	printHex(9, Hex::neighbors(9, height, width, true));
	printHex(10, Hex::neighbors(10, height, width, true));
	printHex(11, Hex::neighbors(11, height, width, true));
	std::cout << std::endl;
}
