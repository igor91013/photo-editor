#pragma once
#include "Picture.h"
#include "Operation.h"
class Mediana : public Operation {
	Picture picture;
	size_t width, height;
	std::vector<Pixel>* pixels = nullptr;
	const std::vector<Pixel>* pixels2 = nullptr;

public:        
	Mediana(const Picture& p) : picture(p) {
		pixels = picture.getPixels();
		pixels2 = p.getPixels();
		width = picture.getWidth();
		height = picture.getHeight();
	}
	             
	virtual void operator()(Pixel&) override;

	void save(std::ostream& out, int level) const override{}

	void load(std::istream& in){}



	                                

	};


