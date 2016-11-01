//
// Created by Andrew Morris on 11/20/15.
//

#ifndef EDITOR_H
#define EDITOR_H

#include "Image.h"

class Editor {
public:
    Editor();
    void Gauss(Image&, Image&);
    void Histogram(Image&, Image&);
    void Kirsch(Image&, Image&);
    void FillIn(Image&, Image&);
    void Thinning(Image&, Image&);
    void Hough_Transform(Image&, Image&);
    void windowNoiseReduction(Image&, Image&, int winSize);

private:
    int add(int);
    int subtract(int);

};


#endif //IMAGEREC_EDITOR_H
