#pragma once
#include "BasicOperations.h"
#include <set>
#include <algorithm>


class CompositeOperation : public Operation {
	std::vector<Operation*> operations;
	int cnt=0;


public:
	CompositeOperation() {}

	CompositeOperation(const CompositeOperation&) = delete;

	CompositeOperation& operator=(const CompositeOperation& c) = delete;

	~CompositeOperation() { remove(); }
	
	CompositeOperation& addOperation(Operation* op) { operations.push_back(op); cnt++; return *this; }

	void operator()(Pixel& p) override;

	void save(std::ostream& out, int level) const;

	void load(std::istream& in);

	void remove();

	std::vector<Operation*> getOperations() const { return operations; }

	CompositeOperation* read(const char* path);
	
	void write(const char* path, const CompositeOperation&);
	
	
	

	

   

	
	






};

