#include "Pixel.h"
//#include <regex>

std::regex Pixel::rx("([0-9]*),([0-9]*),([0-9]*),([0-9]*)");
std::smatch Pixel::result;

Pixel::Pixel(std::string s){
	if (regex_match(s, result, rx)){
		r = atoi(result.str(1).c_str());
		g = atoi(result.str(2).c_str());
		b = atoi(result.str(3).c_str());
		a = atoi(result.str(4).c_str());
	}
}
