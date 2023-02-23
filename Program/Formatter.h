#pragma once
#include <string>
#include "Picture.h"
class Formatter {

	
public:
	virtual Picture* read(const char*) = 0;
	virtual void write(const char*, const Picture&) = 0;

};  
