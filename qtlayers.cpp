#include "qtlayers.h"

QtLayers::QtLayers() {}

void QtLayers::UpdateRender(Image* img, AspectRatioLabel* imageLabel){
    img->UpdateRender();
    int width = img->GetSize().x;
    int height = img->GetSize().y;

    QImage Qimg(width, height, QImage::Format_ARGB32);

    for(int i=0; i<width; i++){
        for(int j=0; j<height; j++){
            Pixel* p = img->GetRender()[i][j];
            if(img->GetRender()[i][j] == nullptr){
                QRgb color = qRgba(255, 255, 255, 255);
                Qimg.setPixel(i, j, color);
            }
            else{
                QRgb color = qRgba(p->color.R, p->color.G, p->color.B, 255);
                Qimg.setPixel(i, j, color);
            }
        }
    }
    imageLabel->UpdatePixmap(Qimg);
}

void QtLayers::UpdateRenderFromLayer(Layer* layer, AspectRatioLabel* imageLabel){
    int width = layer->GetSize().x;
    int height = layer->GetSize().y;

    QImage Qimg(width, height, QImage::Format_ARGB32);

    for(int i=0; i<width; i++){
        for(int j=0; j<height; j++){
            Pixel* p = layer->GetPixel(vec::IVec2(i, j));
            if(p == nullptr){
                QRgb color = qRgba(255, 255, 255, 255);
                Qimg.setPixel(i, j, color);
            }
            else{
                QRgb color = qRgba(p->color.R, p->color.G, p->color.B, 255);
                Qimg.setPixel(i, j, color);
            }
        }
    }
    imageLabel->UpdatePixmap(Qimg);
}
