#include "BmpFormatter.h"

                                                           
const int8_t BmpFormatter::headerMask[headerSize] = {
    0x42, 0x4D,                                    
    0x00, 0x00, 0x00, 0x00,  // Size of the bitmap file
    0x00, 0x00,
    0x00, 0x00,
    0x36, 0x00, 0x00, 0x00,

    0x28, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,  // Picture width
    0x00, 0x00, 0x00, 0x00,  // Picture height
    0x01, 0x00,
    0x18, 0x00,              // Bits per pixel.
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,  // Bitmap size
    0x13, 0x0B, 0x00, 0x00,
    0x13, 0x0B, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
};

Picture* BmpFormatter::read(const char* path) {
    
    std::ifstream in(path, std::ios::binary);
    if (!in) throw std::exception("*** File not found!");

    int8_t header[headerSize];
    in.read((char*)header, headerSize); 
    if (!in) throw std::exception("*** File header read error!");

    int32_t fileSize = *(int32_t*)(header + 0x02); 
    int32_t bmpWidth = *(int32_t*)(header + 0x12);
    int32_t bmpHeight = *(int32_t*)(header + 0x16);
    int16_t bitsPerPix = *(int16_t*)(header + 0x1C);
    int32_t bmpSize = *(int32_t*)(header + 0x22);

    int16_t bytesPerPix = bitsPerPix / 8;

    uint8_t* buff = new uint8_t[fileSize - headerSize];
    in.read((char*)buff, fileSize - headerSize);   
    if (!in) throw std::exception("*** Pixels read error!");
    in.close();
    

    std::vector<Pixel> bmp;
    size_t cnt = 0;
    for (size_t row = bmpHeight; row > 0; row--) { 
        for (size_t col =0 ; col < bmpWidth ; col++) {  
            Pixel pixel(buff[cnt+2], buff[cnt+1], buff[cnt], (bytesPerPix==4 ? buff[cnt + 3] : 255)); 
            bmp.push_back(pixel);                        
            cnt += bytesPerPix;
        }
        while (cnt % 4 != 0) cnt++; 
    }
    delete[] buff;
    return new Picture(bmp, bmpWidth, bmpHeight);
}

void BmpFormatter::write(const char* path, const Picture& picture) {
    std::ofstream out(path, std::ios::binary);
    if (!out) throw std::exception("*** File open failed!");

    int8_t header[headerSize];
    for (size_t i = 0; i < headerSize; i++)
        header[i] = headerMask[i];
    int16_t bytesPerPix = 3 + withAlpha;
    int32_t bmpWidth = picture.getWidth();
    int32_t bmpHeight = picture.getHeight();
    int32_t bmpSize = bmpWidth * bytesPerPix;
    while (bmpSize % 4 != 0) bmpSize++;
    bmpSize *= bmpHeight;
    int32_t fileSize = bmpSize + headerSize;

    *(int32_t*)(header + 0x02) = fileSize;
    *(int32_t*)(header + 0x12) = bmpWidth;
    *(int32_t*)(header + 0x16) = bmpHeight;
    *(int16_t*)(header + 0x1C) = bytesPerPix * 8;
    *(int32_t*)(header + 0x22) = bmpSize;

    out.write((char*)header, headerSize);
    if (!out) throw std::exception("*** File header write error!");


    uint8_t* buff = new uint8_t[fileSize - headerSize];
    size_t cnt1 = 0;
    size_t cnt2 = 0;
    const std::vector<Pixel>* pixels = picture.getPixels();
    for (size_t row = bmpHeight; row > 0; row--) {
        for (size_t col = 0; col < bmpWidth; col++) { 
            const Pixel& p = (*pixels)[cnt1++]; 
            buff[cnt2++] = (uint8_t)p.getBlue();
            buff[cnt2++] = (uint8_t)p.getGreen();
            buff[cnt2++] = (uint8_t)p.getRed();
            if (withAlpha) 
                buff[cnt2++] = (uint8_t)p.getAlpha();
            
        }
        while (cnt2 % 4 != 0) buff[cnt2++] = 0;
    }
    out.write((char*)buff, bmpSize);
    if (!out) throw std::exception("*** Pixels write error!");
    delete[] buff;

}

