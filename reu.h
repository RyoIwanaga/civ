//// Macro ////

#define REU__PROPERTY(type, var, fnName)							\
private:	type var;												\
public:		virtual type get##fnName() const { return var; }		\
public:		virtual void set##fnName(type var) { this->var = var; } 

typedef int 			sint;
typedef unsigned int 	uint;
typedef long 			slong;
typedef unsigned long 	ulong;

