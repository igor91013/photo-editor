#pragma once
#include <iostream>
class Exceptions{
public:
	 virtual std::string print() { return "Exception thrown"; }
	
};

class UnknownOperation : public Exceptions {
public:
	std::string print() override {
		return "*** Unknown operation called";
	}
};

class IndexingError : public Exceptions {
public:
	std::string print() override {
		return "*** Index out of bounds exception thrown";
	}
};

class NoLayerException : public Exceptions {
public:
	std::string print() override {
		return "*** There is no layers at the moment";
	}
};




