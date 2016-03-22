#include "World.h"
#include "Hex.h"

#include <algorithm>
#include <cassert>
#include <list>
#include <set>
#include <iterator>
#include <random>

#include <iostream>


std::list<int> makeListInRange (int middle, int addSub, int bottom, int upper);
//std::list<Pos> makeListCoastPositions(std::vector<Terrain>* terrains, int height, int width, bool isCylinder);


int aat (int y, int x, int width) 
{
	return y * width + x;	
}

World::Ptr World::createMassive(int height, int width, bool isCylinder, float landPersentage)
{
	int worldSize = height * width;
	int land = worldSize * landPersentage;

	std::random_device rnd;

	auto world = std::make_shared<World>(height, width, isCylinder);
	auto terrains = &(world->terrains);
	auto target = height / 2 * width + width / 2;
	std::set<int> coasts;

	terrains->resize(worldSize);
	terrains->at(target) = Terrain(
			Terrain::BaseType::Glassland,
			Terrain::VerticalType::Flatland,
			Terrain::FeatureType::None);


	// already placed 1
	for (int n = 1; n < land; n++) {
		auto neighbors = Hex::neighbors(target, height, width, isCylinder);
		for (auto n : neighbors) {
			// add coast
			if (terrains->at(n).base == Terrain::BaseType::None) {
				coasts.insert(n);
			}	
		}
		auto targetIndex = rnd() % coasts.size();
		auto itr = coasts.begin();
		std::advance(itr, targetIndex);
		target = *itr;

		// XXX Destructive operation
		terrains->at(target).base = Terrain::BaseType::Glassland;

	}

	for (int i = 0; i < worldSize; i++) {
		if (terrains->at(i).base == Terrain::BaseType::None)
			// XXX Destructive operation
			terrains->at(i).base = Terrain::BaseType::Ocean;
	}

	//			terrain = Terrain(
	//					rnd() % 2 == 0 ? Terrain::BaseType::Glassland : Terrain::BaseType::Ocean,
	//					Terrain::VerticalType::Flatland,
	//					Terrain::FeatureType::None);

	return world;
}

/*

std::set<int> makeSetCoastPositions(std::vector<Terrain>* terrains, int height, int width, bool isCylinder)
{
	std::set<int> coasts;

	// For each square
	for (int y = 2; y < height - 2; y++) {
		for (int x = 2; x < width - 2; x++) {

			auto terrain = &(terrains->at(aat(y, x, width)));

			// Skip If searching square is land
			if (terrain->base == Terrain::BaseType::Glassland)
				continue;

			auto rangeY = makeListInRange(y, 1, 0, height - 1);
			auto rangeX = makeListInRange(x, 1, 0, width - 1);

			// For each neighbor
			for (auto yy : rangeY) {
				for (auto xx : rangeX) {

					if (terrains->at(aat(yy, xx, width)).base == Terrain::BaseType::Glassland) {
						// lst.push_back(terrain);
						lst.push_back(Pos(x, y));

						goto LABEL_FOUND_COAST;
					}
				}
			}

LABEL_FOUND_COAST:
			assert(true);
		}
	}

	return lst;
}
*/


std::list<int> makeListInRange (int middle, int addSub, int bottom, int upper)
{
	std::list<int> lst;

	auto min = std::max (middle - addSub, bottom);
	auto max = std::min (middle + addSub, upper);

	for (int n = min; n <= max; n++) {
		lst.push_back(n);	
	}

	return lst;
}

