#include "Unit.h"

Unit::Unit(ulong pos) :
	pos(pos)
{
}

Unit::~Unit()
{
}

Unit::Ptr Unit::create(ulong pos)
{
	return std::make_shared<Unit>(pos);
}

