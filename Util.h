#ifndef _Util_h_
#define _Util_h_

#include <cassert>

namespace Util {

	namespace Math {

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

		template<typename T>
			inline T addToMax(T base, T value, T max)
			{
				auto result = base + value;

				if (result > max )
					return max;
				else
					return result;
			}

		template<typename T>
			inline T subToMin(T base, T value, T min)
			{
				auto result = base - value;

				if (result < min)
					return min;
				else
					return result;
			}
	}

} // end of namespace Util


#endif // _Util_h_

