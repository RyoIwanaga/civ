#ifndef _reu_h_
#define _reu_h_


#define REU__PROPERTY(type, var, fnName)							\
private:	type var;												\
public:		virtual type get##fnName() const { return var; }		\
public:		virtual void set##fnName(type var) { this->var = var; } 

typedef short			sshort;
typedef unsigned short	ushort;
typedef int 			sint;
typedef unsigned int 	uint;
typedef long 			slong;
typedef unsigned long 	ulong;


#include <algorithm>
#include <list>
#include <functional>

namespace reu {
	namespace list {

		/*
		template <typename T> 
		typename std::list<T>::iterator find(std::list<T> lst, std::function<bool(T)> fnPred)
		{
			auto ite = lst.begin();

			for (; ite != lst.end(); ite++) {
				if (fnPred(*ite))
					(*ite)->getPos();
					return typename ite;
			}

			return ite;
		} */
	}
}

#endif

