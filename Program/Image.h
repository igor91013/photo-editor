#pragma once
#include <iostream>
#include "Layer.h"
#include "Operation.h"
#include "BmpFormatter.h"
#include "Formatter.h"
#include "Selection.h"
#include "CompositeOperation.h"
#include "Exceptions.h"


class Image {
private:
    static Image* image;
    std::vector<Layer*> layers;     
    std::vector<Selection> selections;
    int width=0, height=0;
    Picture *picture = nullptr;
    CompositeOperation* operation = nullptr;
    std::string path;

   Image() {}   

   void clear();
   void doOp(CompositeOperation* op, int row, int col);
public:

    static Image* getImage() {  
        if (image == nullptr)
            image = new Image();
        return image;
    }

    void addLayer(const char* path, Formatter* formatter);

    void addLayer(Layer* layer);

    void deleteLayer(int i);

    void deleteSelection(int i) {
        if (i >= layers.size() || i < 0) throw IndexingError();
        
        selections.erase(selections.begin() + i);
    }

  
    std::vector<Layer*> getLayers() { return layers; }

    void addSelection(Selection s) {
        
        selections.push_back(s);
    }
           
    void applyOperation(CompositeOperation* op);
    
    Picture& createPicture();
    
    Picture& getPicture() { return *picture; }
    const Picture& getPicture() const { return *picture; }

    void setPath(std::string path) {
        this->path = path;
    }
    void save(std::ostream& out, int level) const;

    void load(std::istream& in);

    void setOperation(CompositeOperation* op) { operation = op; }

    std::vector<Selection> getSelections() const { return selections;}

    CompositeOperation* getOperation() const { return operation; }
};
