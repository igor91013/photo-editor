#include "Layer.h"
#include "BmpFormatter.h"
#include "PamFormatter.h"
#include "MyFormatter.h"

Pixel* Layer::getPixel(int row, int col, int height, int width) {
	int hPict = picture->getHeight();
	int wPict = picture->getWidth();
	int r0Pict = (height - hPict) / 2;
	int c0Pict = (width - wPict) / 2;
	if (row >= r0Pict && row < r0Pict + hPict && col >= c0Pict && col < c0Pict + wPict) {
		int rPict = row - r0Pict;
		int cPict = col - c0Pict;
		return &(*picture->getPixels())[rPict * wPict + cPict]; 
	}
	else
		return nullptr;
}

void Layer::save(std::ostream& out, int level) const {
	if (picture == nullptr) throw std::exception("*** Layer is empty!");
	out << std::setw(level * 4) << "" << "Layer " << std::endl; 
	level++;
	out << std::setw(level * 4) << "" <<active <<" "<< visible << " " << path << std::endl;
	//picture->save(out,level);
	BmpFormatter bmp;
	bmp.setWithAlpha(true);
	bmp.write(path.c_str(), *picture);
}



void Layer::load(std::istream& in){
	in >> active >> visible;
	std::getline(in, path); // "C:\Program Files\"
	path = path.substr(1);
	//std::string dummy; in >> dummy;
	//picture = new Picture();
	//picture->load(in);
	std::string substr = path.substr(path.size() - 3);
	Formatter* formatter;
	if (substr == "bmp")
		formatter = new BmpFormatter();
	else if (substr == "pam")
		formatter = new PamFormatter();
	else 
		formatter = new MyFormatter();
	picture = formatter->read(path.c_str());

}
