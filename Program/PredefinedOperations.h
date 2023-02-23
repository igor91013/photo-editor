#pragma once
#include "BasicOperations.h"

class Inversion : public Operation {
public:
	void operator()(Pixel& p) override {
		SubInv(255)(p);  
	}

	void save(std::ostream& out, int level) const override {
		out << std::setw(level * 4) << "" << "Inversion" << std::endl;
	}

	virtual void load(std::istream& in) override {}
};

class Grayscale : public Operation {
public:
	Grayscale() {}
	void operator()(Pixel& p) override {
		int arithmeticMiddle = (p.getRed() + p.getGreen() + p.getBlue())/3;
		p.setRed(arithmeticMiddle);
		p.setGreen(arithmeticMiddle);
		p.setBlue(arithmeticMiddle);
	}

	void save(std::ostream& out, int level) const override {
		out << std::setw(level * 4) << "" << "Grayscale"<<std::endl;
	}

	virtual void load(std::istream& in) override {}

};

class BlackAndWhite : public Operation {
public:
	void operator()(Pixel& p) override {
		int arithmeticMiddle = (p.getRed() + p.getGreen() + p.getBlue()) / 3;
		if (arithmeticMiddle < 127)
			Max(0)(p);
		else
			Min(255)(p);
	}

	void save(std::ostream& out, int level) const override {
		out << std::setw(level * 4) << "" << "BlackAndWhite" << std::endl;
	}

	virtual void load(std::istream& in) override {}
};













