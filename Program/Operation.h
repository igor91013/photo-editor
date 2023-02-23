#pragma once
#include "Pixel.h"
class Operation {
	
public:
	
	virtual void operator()(Pixel&) = 0;

	virtual void save(std::ostream& out, int level) const = 0;

	virtual void load(std::istream& in) = 0;

	virtual ~Operation() {}
};

