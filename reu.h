#ifndef _reu_h_
#define _reu_h_


#define REU__PROPERTY(type, var, fnName)							\
private:	type var;												\
public:		virtual type get##fnName() const { return var; }		\
public:		virtual void set##fnName(type var) { this->var = var; } 

typedef int 			sint;
typedef unsigned int 	uint;
typedef long 			slong;
typedef unsigned long 	ulong;


#include <algorithm>
#include <list>

namespace Reu {

	/*
template <typename T>
T find(std::list<T> lst)
{
	for(T item : lst) {
	}

	return nil;
} */
	
} // end of namespace Reu

#endif

