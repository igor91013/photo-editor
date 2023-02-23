#pragma once
#include <vector>
#include "Rectangle.h"
#include <string>


class Selection {
private:
	std::vector<Rectangle> rectangles;
	//std::string name;
	bool active = true;
	

public:

	bool isActive() const { return active; }
	void setActive(bool a) { active = a; }
	Selection(const std::vector<Rectangle>& rec) : rectangles(rec) {}

	//Selection(std::string name, const std::vector<Rectangle>& rec) : name(name), rectangles(rec) {}
	Selection() {}

	std::vector<Rectangle> getRectangles() { return rectangles; }

	void addRectangle(Rectangle r) { rectangles.push_back(r); };

	//std::string getName()const { return name; }

	bool contains(int row, int col) const;

	void save(std::ostream& out, int level) const;

	void load(std::istream& in);

	friend std::ostream& operator<<(std::ostream & out, const Selection& s);


};
