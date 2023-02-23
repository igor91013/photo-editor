#include "Mediana.h"
                            


void Mediana::operator()(Pixel& pixel) {
	size_t pos = &pixel - &(*pixels2)[0];
	size_t row = pos / width;
	size_t col = pos % width;
	
	int red = 0;
	int green = 0;
	int blue = 0;
	int cnt = 0;
	
	for (int i = -1; i <= 1; i++) { 
		for (int j = -1; j <= 1; j++) {
			if (row + i >= 0 && col + j >= 0 && row + i < height && col + j < width) {
				Pixel& p = (*pixels)[(row + i) * width + (col + j)];
				red += p.getRedInt();
				green += p.getGreenInt();
				blue += p.getBlueInt();
				cnt++;
			}
		}
	}
	pixel.setRed(red / cnt); 
	pixel.setGreen(green / cnt);
	pixel.setBlue(blue / cnt);
	

}
