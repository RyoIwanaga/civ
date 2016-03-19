#include "World.h"

#include <algorithm>
#include <cassert>
#include <list>
#include <iterator>
#include <random>

#include <iostream>


std::list<int> makeListInRange (int middle, int addSub, int bottom, int upper);
std::list<Pos> makeListCoastPositions(std::vector<Terrain>* terrains, int height, int width, bool isCylinder);

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
	auto firstY = height / 2;
	auto firstX = width / 2;

	terrains->resize(worldSize);
	terrains->at(aat(firstY, firstX, width)) = Terrain(
			Terrain::BaseType::Glassland,
			Terrain::VerticalType::Flatland,
			Terrain::FeatureType::None);

	for (int n = 0; n < land; n++) {
		auto coasts = makeListCoastPositions(terrains, height, width, isCylinder);

		if (coasts.size() == 0)
			break;

		auto targetIndex = rnd() % coasts.size();
		auto itr = coasts.begin();
		std::advance(itr, targetIndex);
		auto pos = *itr;

		// XXX Destructive operation
		terrains->at(aat(pos.y, pos.x, width)).base = Terrain::BaseType::Glassland;
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


std::list<Pos> makeListCoastPositions(std::vector<Terrain>* terrains, int height, int width, bool isCylinder) // TODO Cylinder
{
	std::list<Pos> lst;

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

