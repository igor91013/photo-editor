#include "MyFormatter.h"

Picture* MyFormatter::read(const char* path) {
	std::ifstream in(path);
	if (!in) throw std::exception("*** File open failed!");
	Picture* pict = new Picture();
	std::string dummy; in >> dummy;
	pict->load(in);
	in.close();
	return pict;
}


void MyFormatter::write(const char* path, const Picture& pict) {
	std::ofstream out(path);
	if (!out) throw std::exception("*** File open failed!");
	pict.save(out, 0);
	out.close();
}


