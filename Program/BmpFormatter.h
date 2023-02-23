#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include "Picture.h"
#include "Formatter.h"


class BmpFormatter : public Formatter {
    static const size_t headerSize = 54;
    static const int8_t headerMask[headerSize];
    bool withAlpha = false;


public:
    BmpFormatter(bool withAlpha = false) { this->withAlpha = withAlpha; }

    Picture* read(const char*) override;

    void write(const char*, const Picture&) override;

    bool getWithAlpha() const { return withAlpha; }

    void setWithAlpha(bool withAlpha) {
        this->withAlpha = withAlpha;
    }
};

