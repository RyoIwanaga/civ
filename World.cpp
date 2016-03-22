#include "World.h"
#include "Hex.h"

#include <cassert>
#include <list>
#include <set>
#include <iterator>
#include <random>


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
			auto y = n / width;
			auto x = n % width;

			if (y <= 0 
					|| height - 1 <= y 
					|| x <= 1
					|| width - 2 <= x)
				continue;

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

