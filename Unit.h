#ifndef _Unit_h_
#define _Unit_h_

#include "Strategy.h"

class Unit
{
	REU__PROPERTY(ulong, pos, Pos);

public:
	typedef std::shared_ptr<Unit> Ptr;
	static Ptr create(ulong pos);

	Unit(ulong pos);
	virtual ~Unit();
};


#endif // _Unit_h_

