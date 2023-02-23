#pragma once
#include "Formatter.h"
#include <fstream>
#include <iostream>
#include "Picture.h"
#include "CompositeOperation.h"

class MyFormatter :	public Formatter
{
public:
	Picture* read(const char*) override;
	void write(const char*, const Picture&) override;

	
};

