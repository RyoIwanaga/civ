#include "Unit.h"

Unit::Unit(Unit::Type t, ushort owner, ulong pos, int hp, int damage) :
	type(t),
	owner(owner),
	pos(pos),
	hp(hp),
	hpMax(hp),
	damage(damage)
{
}

Unit::~Unit()
{
}

Unit::Ptr Unit::create(Type t, ushort owner, ulong p)
{
	switch (t) {
	case Unit::Type::Settler:
		return std::make_shared<Unit>(Unit::Type::Settler, owner, p, 100, 20);
	case Unit::Type::Warrior:
		return std::make_shared<Unit>(Unit::Type::Warrior, owner, p, 100, 20);

	default:
		assert(false);
	}
}

