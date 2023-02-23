#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include "Picture.h"
#include "Formatter.h"


class PamFormatter : public Formatter {
public:
    PamFormatter() {}

    Picture* read(const char*) override;

    void write(const char*, const Picture&) override;

};
