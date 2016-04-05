#ifndef _Util_h_
#define _Util_h_

#include <cassert>

namespace Util {

	inline int addCircle(int base, int add, int max, int min = 0) 
	{
		assert(max >= min);

		int range = max - min + 1;
		int moveFromMin = (base - min + add) % range;

		if (moveFromMin >= 0)
			return min + moveFromMin;
		else
			return max + moveFromMin + 1;

	}

} // end of namespace Util


#endif // _Util_h_

