#include <fstream>
#include "CompositeOperation.h"
#include "Exceptions.h"
#include "PredefinedOperations.h"


void CompositeOperation::operator()(Pixel& p) {   
	for (Operation* o : operations)
		o->operator()(p);
}

void CompositeOperation::save(std::ostream& out, int level) const {
	out << std::setw(level * 4) << "" << "CompositeOperation " << operations.size() << std::endl;
	level++;
	for (Operation* o : operations)
		o->save(out, level);
}

void CompositeOperation::load(std::istream& in) {
	int n;
	in >> n;
	for (int i = 0; i < n; i++) {
		std::string name;
		in >> name;
		Operation* op = nullptr;
		if (name == "Add") {
			op = new Add();
		}
		else if (name == "Sub") {
			op = new Sub();
		}
		else if (name == "SubInv") {
			op = new SubInv();
		}
		else if (name == "Mul") {
			op = new Mul();
		}
		else if (name == "Div") {
			op = new Div();
		}
		else if (name == "DivInv") {
			op = new DivInv();
		}
		else if (name == "Pow") {
			op = new Pow();
		}
		else if (name == "Log") {
			op = new Log();
		}
		else if (name == "Transparency") {
			op = new Transparency();
		}
		else if (name == "Grayscale") {
			op = new Grayscale();
		}
		else if (name == "BlackAndWhite") {
			op = new BlackAndWhite();
		}
		else if (name == "Inversion") {
			op = new Inversion();
		}
		else if (name == "Max") {
			op = new Max();
		}
		else if (name == "Min") {
			op = new Min();
		}
		else if (name == "Abs") {
			op = new Abs();
		}
		else if (name == "SetPixel") { 
			op = new SetPixel();
		}
		else if (name == "CompositeOperation") {
			op = new CompositeOperation();
		}
		else 
			throw UnknownOperation();
		
		op->load(in);
		operations.push_back(op);
	}
}

void CompositeOperation::remove() {
	for (int i = 0; i < cnt; i++) {
		delete operations[i];
	}
	operations.clear();
}

CompositeOperation* CompositeOperation::read(const char* path) {
	std::ifstream in(path);
	if (!in) throw std::exception("*** File open failed!");
	CompositeOperation* cp = new CompositeOperation();
	std::string dummy;
	in >> dummy;
	cp->load(in);
	in.close();
	return cp;
}

void CompositeOperation::write(const char* path, const CompositeOperation& cp) {
	std::ofstream out(path);
	if (!out) throw std::exception("*** File open failed!");
	cp.save(out, 0);
	out.close();
}






