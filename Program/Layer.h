#pragma once
#include "Picture.h"
#include <string>
#include "Formatter.h"

class Layer{
	bool active = true;
	bool visible = true;
	Picture* picture = nullptr;
	std::string path;

public:
	Layer(){}
	
	Layer(const char* path, Formatter* formatter) {
		picture = formatter->read(path);
		this->path = path;
	}

	Layer(Picture* picture) { 
		if (picture==nullptr) throw std::exception("*** Layer is empty!"); 
		this->picture = picture;
	}

	Layer(const Layer&) = delete;

	void operator=(const Layer&) = delete;

	~Layer() { delete picture; }

	bool isActive() const { return active; }

	bool isVisible() const { return visible; }

	void setActive(bool s) { active = s; }

	void setVisible(bool s) { visible = s; }

	int getWidth() const { return picture->getWidth(); }
	
	int getHeight() const { return picture->getHeight(); }

	Pixel* getPixel(int row, int col, int height, int width);

	Picture* getPicture() { return picture; }

	void save(std::ostream& out, int level) const;

	void load(std::istream& in);

	


};

