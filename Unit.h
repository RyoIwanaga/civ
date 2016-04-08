#ifndef _Unit_h_
#define _Unit_h_

#include "Strategy.h"

class Unit
{
public: 
	enum class Type {
		Settler = 0,
		Scout,
		Warrior,
		Archer,
	};

	REU__PROPERTY(Type, type, Type);
	REU__PROPERTY(ushort, owner, Owner);
	REU__PROPERTY(ulong, pos, Pos);
	REU__PROPERTY(uint, hp, Hp);
	REU__PROPERTY(int, hpMax, HpMax);
	REU__PROPERTY(int, damage, Damaege);

public:
	typedef std::shared_ptr<Unit> Ptr;
	static Ptr create(Type t, ushort owner, ulong pos);

	Unit(Type t, ushort owner, ulong pos, int hp, int damage);
	virtual ~Unit();
};


#endif // _Unit_h_

