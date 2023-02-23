#pragma once
#include <iostream>
#include <algorithm>
#include "Exceptions.h"
#include "Image.h"
#include "BmpFormatter.h"
#include "PredefinedOperations.h"
#include "MyFormatter.h"
#include "PamFormatter.h"
#include "Mediana.h"
class UserInteraction{
private: 
	int argc;
    const char** argv;
	
	
public:
	UserInteraction(int argc, const char* argv[]) {
		this->argc = argc;
		this->argv = argv;
		start(); 
	}

	void start();
	void normalMode();
	void automaticMode();
	
	void layersI(Image& image);
	void toolsI(Image& image);
	void exportI(Image& image);
	void exitI(Image& image);
	void openI(Image& image);
	void saveI(Image& image);
	void loadI(Image& image);
	void selecI(Image& image);
	void opI(Image& image);
	void deleteLayerI(Image& image);
};

