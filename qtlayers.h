#ifndef QTLAYERS_H
#define QTLAYERS_H

#include "src/Image.hpp"
#include "aspectratiolabel.h"
#include <QLabel>

class QtLayers
{
public:
    QtLayers();

    static void UpdateRender(Image* img, AspectRatioLabel* imageLabel);
    static void UpdateRenderFromLayer(Layer* layer, AspectRatioLabel* imageLabel);
};

#endif // QTLAYERS_H
