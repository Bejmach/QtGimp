#include "dialoggaussian.h"
#include "ui_dialoggaussian.h"
#include "src/LayerEditor.hpp"
#include "qtlayers.h"

DialogGaussian::DialogGaussian(QWidget *parent, AspectRatioLabel* _label, Image* _img, LE::Operations _operations)
    : QDialog(parent)
    , ui(new Ui::DialogGaussian)
{
    ui->setupUi(this);

    label = _label;
    img = _img;

    kernelSize = ui->spinBox;
    sigma = ui->doubleSpinBox;
    operations = _operations;
}

DialogGaussian::~DialogGaussian()
{
    delete ui;
}

void DialogGaussian::DecideFunction(){
    if(operations == LE::Operations::GaussianBlur){
        LE::GaussianBlur(img, kernelSize->value(), sigma->value());
    }
    else if(operations == LE::Operations::PseudoFresnel){
        LE::PseudoFresnel(img, kernelSize->value(), sigma->value());
    }
}

void DialogGaussian::on_pushButton_pressed()
{
    DecideFunction();
    img->UpdateRender();
    QtLayers::UpdateRender(img, label);
}


void DialogGaussian::on_buttonBox_accepted()
{
    DecideFunction();
    LE::Apply(img);
    img->UpdateRender();
    QtLayers::UpdateRender(img, label);
    this->close();
}

void DialogGaussian::on_buttonBox_rejected()
{
    LE::Revert(img);
    img->UpdateRender();
    QtLayers::UpdateRender(img, label);
    this->close();
}
