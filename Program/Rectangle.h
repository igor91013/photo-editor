#pragma once
#include <iostream>
class Rectangle {
private:
	int row, col;
	int width, height;

public:
	Rectangle(int row, int col, int width, int height) : row(row), col(col), width(width), height(height) {}
	Rectangle(std::string s);

	int getRow() const { return row; }
	int getCol() const { return col; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }

	bool contains(int row, int col) const {
		return row >= this->row && row < this->row + width && col >= this->col && col < this->col + height;
	}

	
	friend std::ostream& operator<<(std::ostream& out, const Rectangle& r) {
		return out << r.row << "," << r.col << "," << r.width << "," << r.height;
	}
	


	


};