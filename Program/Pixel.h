#pragma once
#include <iostream>
#include <regex>



class Pixel {
private:
	int r, g, b, a;
	static std::regex rx;
	static std::smatch result;

public:
	Pixel(int r, int g, int b , int a = 0xff ) : r(r), g(g), b(b), a(a) {}
	Pixel() {}
	Pixel(std::string s);
	
	int getRed() const { return (r < 0) ? 0 : (r > 255) ? 255 : r; }
	int getGreen() const { return (g < 0) ? 0 : (g > 255) ? 255 : g; }
	int getBlue() const { return (b < 0) ? 0 : (b > 255) ? 255 : b; }
	int getAlpha() const { return (a < 0) ? 0 : (a > 255) ? 255 : a; }

	int getRedInt() const { return r; }
	int getGreenInt() const { return g; }
	int getBlueInt() const { return b; }
	int getAlphaInt() const { return a; }

	void setRed(int r)  { this->r=r; }
	void setBlue(int b)  { this->b = b; }
	void setGreen(int g) { this->g = g; }
	void setAlpha(int a) { this->a = a; }

	double getAlphaPercent() const { return a / 255; }

	

	friend std::ostream& operator<<(std::ostream& out, const Pixel& p) {
		return out << p.r << ',' << p.g << ',' << p.b << ',' << p.a;
	}

	 










};
