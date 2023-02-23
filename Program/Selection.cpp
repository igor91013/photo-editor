#include "Selection.h"
#include <iomanip>


bool Selection::contains(int row, int col) const {
	for (Rectangle r : rectangles)
		if (r.contains(row, col))
			return true;
	return false;
}

std::ostream& operator<<(std::ostream& out, const Selection& s) {
	//out << s.name << std::endl;
	for (Rectangle r : s.rectangles) {
		out << r << ' ';
	}
	return out;
}   

void Selection::save(std::ostream& out, int level) const
{
	out << std::setw(level * 4) << "" << "Selection" << std::endl; //sto ovaj warning, i zasto koristimo size_t kod picturea w i h 
	level++;
	//out << std::setw(level * 4) << "" << name << std::endl;
	out << std::setw(level * 4) << "" << active << std::endl;
	out << std::setw(level * 4) << "" << rectangles.size();
	for (Rectangle r : rectangles) {
		out << ' ' << r;
	}
	out << std::endl;
}

void Selection::load(std::istream& in)
{
	int n;
	//in >> name >> active >> n;
	in >> active >> n;
	for (int i = 0; i < n; i++) {
		std::string s;
		in >> s;
		rectangles.push_back(Rectangle(s));
	}

}
