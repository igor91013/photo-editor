#include "Picture.h"

Picture::Picture(int width, int height, const Pixel& pixel) : width(width), height(height) {
	for (int i = 0; i < height * width; i++)
		pixels.push_back(pixel);
}

void Picture::setWidth(int width) {
	this->width = width;
}

void Picture::setHeight(int height) {
	this->height = height;
}

void Picture::save(std::ostream& out, int level) const
{
	out << std::setw(level * 4) << "" << "Picture" << std::endl;
	level++;
	out << std::setw(level * 4) << "" << width << " " << height << std::endl;
	for (size_t row = 0; row < height; row++) {
		out << std::setw(level * 4) << "";  
			for (size_t col = 0; col < width; col++)
				out << pixels[row * width + col] << ' ';
		out << '\n';
	}
}

void Picture::load(std::istream& in)
{
	in >> width >> height;  
	for (size_t row = 0; row < height; row++) {
		std::cout << "Picture.load - row " << row << "\n";
		for (size_t col = 0; col < width; col++) {
			std::string s;
			in >> s;
			pixels.push_back(Pixel(s));
		}
	}
}


