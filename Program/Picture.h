#pragma once
#include <vector>
#include "Pixel.h"
#include <algorithm>
#include <iomanip>

class Picture {
private:
	std::vector<Pixel> pixels;    
	size_t width=0, height=0;
	
public:     
	Picture(int width, int height, const Pixel& pixel);
	Picture(){}
	
	void setWidth(int width);
	void setHeight(int height);

	Picture(const std::vector<Pixel>& pixels, size_t width, size_t height): pixels(pixels), width(width), height(height){
		
	}

	size_t getWidth() const { return width; }
	size_t getHeight() const { return height; }
	const std::vector<Pixel>* getPixels() const { return &pixels; }
	std::vector<Pixel>* getPixels() { return &pixels; }

	
	void save(std::ostream& out, int level) const;
	void load(std::istream& in);
	


};
