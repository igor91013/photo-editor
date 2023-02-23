#pragma once
#include <iostream>
#include "Operation.h"
#include "Pixel.h"
#include <math.h>
#include <queue>
#include <iomanip>


class Add : public Operation {
	int value;

public:
	Add(int v=0) : value(v) {}

	void operator()(Pixel& p) override {
		p.setRed(p.getRedInt() + value);
		p.setGreen(p.getGreenInt() + value);
		p.setBlue(p.getBlueInt() + value);
	}

	void save(std::ostream& out, int level) const override  {
		out << std::setw(level * 4) << "" << "Add " << value << std::endl;
	}

	virtual void load(std::istream& in) override {
		in >> value;
	}
};   

class Sub : public Operation {
	int value;
public:
	Sub(int v=0) :value(v) {}

	void operator()(Pixel& p) override {
		p.setRed(p.getRedInt() - value);
		p.setGreen(p.getGreenInt() - value);
		p.setBlue(p.getBlueInt() - value);
	}

	void save(std::ostream& out, int level) const override {
		out << std::setw(level * 4) << "" << "Sub " << value << std::endl;
	}

	virtual void load(std::istream& in) override {
		in >> value;
	}
};

class SubInv : public Operation {
	int value;
public:
	SubInv(int v=0) :value(v) {}

	
	void operator()(Pixel& p) override {
		p.setRed(value - p.getRedInt());
		p.setGreen(value - p.getGreenInt());
		p.setBlue(value - p.getBlueInt());
	}

	void save(std::ostream& out, int level) const override {
		out << std::setw(level * 4) << "" << "SubInv " << value << std::endl;
	}

	virtual void load(std::istream& in) override {
		in >> value;
	}
};

class Mul : public Operation {
	int value;
public:
	Mul(int v=1) :value(v) {}

	void operator()(Pixel& p) override {
		p.setRed(p.getRedInt() * value);
		p.setGreen(p.getGreenInt() * value);
		p.setBlue(p.getBlueInt() * value);
	}

	void save(std::ostream& out, int level) const override {
		out << std::setw(level * 4) << "" << "Mul " << value << std::endl;
	}

	virtual void load(std::istream& in) override {
		in >> value;
	}
};

class Div : public Operation {
	int value;
public:
	Div(int v=1) :value(v) {}

	void operator()(Pixel& p) override {
		p.setRed(p.getRedInt() / value);
		p.setGreen(p.getGreenInt() / value);
		p.setBlue(p.getBlueInt() / value);
	}

	void save(std::ostream& out, int level) const override {
		out << std::setw(level * 4) << "" << "Div " << value << std::endl;
	}

	virtual void load(std::istream& in) override {
		in >> value;
	}
};

class DivInv : public Operation {
	int value;
public:
	DivInv(int v=1) :value(v) {}

	void operator()(Pixel& p) override {
		p.setRed(value / p.getRedInt());
		p.setGreen(value / p.getGreenInt());
		p.setBlue(value / p.getBlueInt());
	}

	void save(std::ostream& out, int level) const override {
		out << std::setw(level * 4) << "" << "DivInv " << value << std::endl;
	}

	virtual void load(std::istream& in) override {
		in >> value;
	}
};

class Pow : public Operation {
	int value;
public:
	Pow(int v=1) :value(v) {}

	void operator()(Pixel& p) override {
		p.setRed((int)pow(p.getRedInt(), value));
		p.setGreen((int)pow(p.getGreenInt(), value));
		p.setBlue((int)pow(p.getBlueInt(), value));
	}
	void save(std::ostream& out, int level) const override {
		out << std::setw(level * 4) << "" << "Pow " << value << std::endl;
	}

	virtual void load(std::istream& in) override {
		in >> value;
	}
};

class Log : public Operation {  
public:
	void operator()(Pixel& p) override {
		if (p.getRedInt() != 0)
			p.setRed((int)log(p.getRedInt()));
		if (p.getGreenInt() != 0)
			p.setGreen((int)log(p.getGreenInt()));
		if (p.getBlueInt() != 0)
			p.setBlue((int)log(p.getBlueInt()));
	}

	void save(std::ostream& out, int level) const override {
		out << std::setw(level * 4) << "" << "Log" << std::endl;
	}

	virtual void load(std::istream& in) override {}
};

class Abs : public Operation {
public:
	void operator()(Pixel& p) override {
		if (p.getRedInt() < 0)
			p.setRed(p.getRedInt() * (-1));
		if (p.getGreenInt() < 0)
			p.setGreen(p.getGreenInt() * (-1));
		if (p.getBlueInt() < 0)
			p.setBlue(p.getBlueInt() * (-1));
	}

	void save(std::ostream& out, int level) const override {
		out << std::setw(level * 4) << "" << "Abs" << std::endl;
	}

	virtual void load(std::istream& in) override {} 
};

class Min : public Operation {   
	int value;
public:
	Min(int v=0) :value(v) {}
	void operator()(Pixel& p) override {
		if (p.getRedInt() < value)
			p.setRed(value);
		if (p.getGreenInt() < value)
			p.setGreen(value);
		if (p.getBlueInt() < value)
			p.setBlue(value);
	}

	void save(std::ostream& out, int level) const override {
		out << std::setw(level * 4) << "" << "Min " << value << std::endl;
	}

	virtual void load(std::istream& in) override {
		in >> value;
	}
};

class Max : public Operation {
	int value;
public:
	Max(int v=255) :value(v) {}
	void operator()(Pixel& p) override {
		if (p.getRedInt() > value)
			p.setRed(value);
		if (p.getGreenInt() > value)
			p.setGreen(value);
		if (p.getBlueInt() > value)
			p.setBlue(value);
	}

	void save(std::ostream& out, int level) const override {
		out << std::setw(level * 4) << "" << "Max " << value << std::endl;
	}

	virtual void load(std::istream& in) override {
		in >> value;
	}
};

class SetPixel : public Operation {
	Pixel pix;
public:
	SetPixel(){}

	SetPixel(const Pixel& p) : pix(p) {}

	void operator()(Pixel& p) override { p = pix; }

	void save(std::ostream& out, int level) const override {
		out << std::setw(level * 4) << "" << "SetPixel " << pix << std::endl;
	}

	virtual void load(std::istream& in) override {
		std::string s;
		in >> s;
		pix = Pixel(s);    
	}
};

class Transparency : public Operation {
	int value=100;
public:
	Transparency() {}
	Transparency(int v) : value(v) {}
	void operator()(Pixel& p) override { p.setAlpha(value * 2.55); }

	void save(std::ostream& out, int level) const override {
		out << std::setw(level * 4) << "" << "Transparency " << value << std::endl;
	}

	virtual void load(std::istream& in) override {
		in >> value;
	}
};


