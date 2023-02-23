#include "Image.h"

Image* Image::image = nullptr;

#include "BasicOperations.h"
void Image::doOp(CompositeOperation* op, int row, int col)
{
	for (Layer* l : layers)
		if (l->isActive()) {
			Pixel* p = l->getPixel(row, col, height, width);
			if (p != nullptr) {
				(*op)(*p);
			}
		}
}

void Image::deleteLayer(int i) {
	if (i >= layers.size() || i < 0) throw IndexingError();
	int oldHeight = layers[i]->getHeight();
	int oldWidth = layers[i]->getWidth();
	delete layers[i];
	layers.erase(layers.begin() + i);
	if (oldHeight == height) {
		int maxh = 0;
		for (int j = 0; j < layers.size(); j++)
			if (layers[j]->getHeight() > maxh)
				maxh = layers[j]->getHeight();
		height = maxh;
	}
	if (oldWidth == width) {
		int maxw = 0;
		for (int j = 0; j < layers.size(); j++)
			if (layers[j]->getWidth() > maxw)
				maxw = layers[j]->getWidth();
		width = maxw;
	}
}


void Image::applyOperation(CompositeOperation* op) {
	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++)
			if (selections.empty()) {
				doOp(op, row, col);
			}
			else
				for (Selection s : selections)
					if (s.isActive() && s.contains(height - 1 - row, col)) {
						doOp(op, row, col);
						break;
					}
}

Picture& Image::createPicture() {
	delete picture;
	picture = new Picture(width, height, Pixel(180, 180, 180, 127));
	std::vector<Pixel>& pixels = *picture->getPixels();
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			for (int lay = 0; lay < layers.size(); lay++) {
				if (layers[lay]->isVisible()) {
					Pixel* pix0 = layers[lay]->getPixel(row, col, height, width);
					if (pix0 != nullptr) {
						int ind = row * width + col;
						Pixel& pix1 = pixels[ind];
						double a0 = pix0->getAlpha() / 255.;
						double a1 = pix1.getAlpha() / 255.;
						double a = a0 + (1 - a0) * a1;
						int r = (int)((pix0->getRed() * a0 + (1 - a0) * a1 * pix1.getRed()) / a + 0.5);
						int g = (int)((pix0->getGreen() * a0 + (1 - a0) * a1 * pix1.getGreen()) / a + 0.5);
						int b = (int)((pix0->getBlue() * a0 + (1 - a0) * a1 * pix1.getBlue()) / a + 0.5);
						pixels[ind] = Pixel(r, g, b, (int)(a * 255 + 0.5));
					}
				}
			}
		}
	}
	return *picture;
}

void Image::save(std::ostream& out, int level) const {
	out << std::setw(level * 4) << "" << "Image" << std::endl;
	level++;
	out << std::setw(level * 4) << "" << width << " " << height << std::endl;
	for (Layer* layer : layers)
		layer->save(out, level);
	if (picture != nullptr) {
		//picture->save(out, level);
		out << std::setw(level * 4) << "" << "Picture\n";
		BmpFormatter bmp;
		bmp.setWithAlpha(true);
		bmp.write(path.c_str(), *picture);
	}
	for (Selection s : selections)
		s.save(out, level);
	if (operation != nullptr)
		operation->save(out, level);
	out << std::setw(level * 4) << "" << "END" << std::endl;
}

void Image::load(std::istream& in) {
	clear();
	in >> width >> height;
	while (true) {
		std::string name; in >> name;
		std::cout << "====== " << name << "\n";
		if (name == "END") break;
		if (name == "Layer") {
			Layer* layer = new Layer();
			layer->load(in);
			layers.push_back(layer);
		}
		else if (name == "Picture") {
			//picture = new Picture();
			//picture->load(in);
			BmpFormatter bmp;
			picture = bmp.read(path.c_str());

		}
		else if (name == "Selection") {
			Selection s;
			s.load(in);
			selections.push_back(s);
		}
		else if (name == "CompositeOperation") {
			operation = new CompositeOperation();
			operation->load(in);
		}
		else
			throw std::exception((std::string("*** Unknown data type ") + name).c_str());
	}
}

void Image::clear()
{
	for (Layer* layer : layers) delete layer;
	layers.clear();
	selections.clear();
	delete picture; picture = nullptr;
	delete operation; operation = nullptr;
}

void Image::addLayer(const char* path, Formatter* formatter) {
	Layer* layer = new Layer(path, formatter);
	addLayer(layer);
}

void Image::addLayer(Layer* layer) {
	if (layer->getWidth() > width)
		width = layer->getWidth();
	if (layer->getHeight() > height)
		height = layer->getHeight();
	layers.push_back(layer);
}