#include "PamFormatter.h"
#include <string>

Picture* PamFormatter::read(const char* path) {

    std::ifstream in(path, std::ios::binary);
    if (!in) throw std::exception("*** File not found!");

    int32_t bmpWidth;
    int32_t bmpHeight;
    std::string dummy;
    in >> dummy;              // P7
    in >> dummy >> bmpWidth;  // WIDTH w
    in >> dummy >> bmpHeight; // HEIGHT h
    in >> dummy >> dummy;     // DEPTH d
    in >> dummy >> dummy;     // MAXVAL m
    in >> dummy >> dummy;     // TUPLETYPE t
    in >> dummy;              // ENDHDR
    in.get();
   
    int32_t bmpSize = bmpWidth * bmpHeight * 4;

    uint8_t* buff = new uint8_t[bmpSize];
    in.read((char*)buff, bmpSize);
    if (!in) throw std::exception("*** Pixels read error!");
    in.close();

    std::vector<Pixel> bmp;
    for (size_t row = bmpHeight; row > 0; row--) {
        for (size_t col = 0; col < bmpWidth; col++) {
            size_t cnt = ((row - 1) * bmpWidth + col) * 4;
            Pixel pixel(buff[cnt + 2], buff[cnt + 1], buff[cnt], buff[cnt + 3]);  
            bmp.push_back(pixel);
        }
    }
    delete[] buff;
    return new Picture(bmp, bmpWidth, bmpHeight);
}

void PamFormatter::write(const char* path, const Picture& picture) {
    std::ofstream out(path, std::ios::binary);
    if (!out) throw std::exception("*** File open failed!");

    int32_t bmpWidth = picture.getWidth();
    int32_t bmpHeight = picture.getHeight();
    int32_t bmpSize = bmpWidth * bmpHeight * 4;

    std::string header =
        "P7\nWIDTH " + std::to_string(bmpWidth) + "\n" +
        "HEIGHT " + std::to_string(bmpHeight) + "\n" +
        "DEPTH 4\n" +
        "MAXVAL 255\n" +
        "TUPLETYPE RGB_ALPHA\n" +
        "ENDHDR\n"
     ;
    
    out << header;
    if (!out) throw std::exception("*** File header write error!");

    uint8_t* buff = new uint8_t[bmpSize];
    size_t cnt2 = 0;
    const std::vector<Pixel>* pixels = picture.getPixels();
    for (size_t row = bmpHeight; row > 0; row--) {
        for (size_t col = 0; col < bmpWidth; col++) { 
            const Pixel& p = (*pixels)[(row-1)*bmpWidth+col];
            buff[cnt2++] = (uint8_t)p.getBlue();
            buff[cnt2++] = (uint8_t)p.getGreen();
            buff[cnt2++] = (uint8_t)p.getRed();
            buff[cnt2++] = (uint8_t)p.getAlpha();
        }
    }
    out.write((char*)buff, bmpSize);
    if (!out) throw std::exception("*** Pixels write error!");
    delete[] buff;
}
