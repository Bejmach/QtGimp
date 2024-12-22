#include "dialogslider.h"
#include "ui_dialogslider.h"
#include "src/Image.hpp"
#include "qtlayers.h"
#include "src/LayerEditor.hpp"

#include <QLabel>

DialogSlider::DialogSlider(QWidget *parent, AspectRatioLabel* _imageLabel, Image* _img, double min, double max, int decimals, LE::Operations _operation)
    : QDialog(parent)
    , ui(new Ui::DialogSlider)
{
    ui->setupUi(this);

    img = _img;
    imageLabel = _imageLabel;
    layer = img->GetLayer(img->focusedLayerId);
    ui->SpinBox1->setMinimum(min);
    ui->SpinBox1->setMaximum(max);
    ui->SpinBox1->setDecimals(decimals);
    ui->SpinBox1->setValue(0);
    Operation = _operation;
}

DialogSlider::~DialogSlider()
{
    delete ui;
}

void DialogSlider::on_buttonBox_accepted()
{
    LE::Apply(img);
    img->UpdateRender();
    QtLayers::UpdateRender(img, imageLabel);
    this->close();
}


void DialogSlider::on_buttonBox_rejected()
{
    LE::Revert(img);
    img->UpdateRender();
    QtLayers::UpdateRender(img, imageLabel);
    this->close();
}
void DialogSlider::on_SpinBox1_valueChanged(double arg1)
{
    if(Operation == LE::Operations::Saturation){
        LE::Saturation(img, arg1);
    }
    else if(Operation == LE::Operations::Brightness){
        LE::Brightness(img, arg1);
    }
    else if(Operation == LE::Operations::Contrast){
        LE::Contrast(img, arg1);
    }
    else if(Operation == LE::Operations::Sobel){
        LE::Sobel(img, arg1);
    }
    else if(Operation == LE::Operations::SobelOut){
        LE::SobelOutline(img, arg1);
    }
    else if(Operation == LE::Operations::Noise){
        LE::Noise(img, arg1);
    }
    else if(Operation == LE::Operations::NoiseG){
        LE::NoiseG(img, arg1);
    }
    else if(Operation == LE::Operations::NoiseGMult){
        LE::NoiseG(img, arg1);
    }
    QtLayers::UpdateRender(img, imageLabel);
}

