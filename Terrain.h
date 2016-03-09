#ifndef _Terrain_h_
#define _Terrain_h_

class Terrain 
{
public:
	enum class BaseType {
		None,
		Glassland, 	// 2 0 0
		Plains,		// 1 1 0
		Tundra,		// 1 0 0
		Desert,		// 0 0 0 
		Ice,		// 0 0 0
		Lake,
		Coast,
		Ocean,
	};

	enum class VerticalType {
		Flatland,
		Hill,
		Peak,
	};

	enum class FeatureType {
		None,
		FloodPlain,	// 3 0 1
		Forest,		// 0 +1 0
		Jungle,		// -1 0 0
		Oasis,		// 3 0 2
	};

	BaseType base;
	VerticalType vertical;
	FeatureType feature;

	Terrain (BaseType base, VerticalType vertical, FeatureType feature) :
		base(base),
		vertical(vertical),
		feature(feature)
	{}

	Terrain () :
		base(BaseType::None),
		vertical(VerticalType::Flatland),
		feature(FeatureType::None)
	{}
};

#endif // _Tile_h_

