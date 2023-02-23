#include "Rectangle.h"
#include <regex>

Rectangle::Rectangle(std::string s) {
	std::regex rx("([0-9]*),([0-9]*),([0-9]*),([0-9]*)");
	std::smatch result;
	if (regex_match(s, result, rx)) {
		row = atoi(result.str(1).c_str());
		col = atoi(result.str(2).c_str());
		width = atoi(result.str(3).c_str());
		height = atoi(result.str(4).c_str());
	}
}
