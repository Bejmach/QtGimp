#include "dialogfresnel.h"
#include "ui_dialogfresnel.h"
#include "src/LayerEditor.hpp"
#include "qtlayers.h"

DialogFresnel::DialogFresnel(QWidget *parent, AspectRatioLabel* _label, Image* _img, LE::Operations _operations)
    : QDialog(parent)
    , ui(new Ui::DialogFresnel)
{
    ui->setupUi(this);

    label = _label;
    img = _img;

    kernelSize = ui->spinBox;
    sigma = ui->doubleSpinBox;
    operations = _operations;

    colorR = ui->spinBoxR;
    colorG = ui->spinBoxG;
    colorB = ui->spinBoxB;
}

DialogFresnel::~DialogFresnel()
{
    delete ui;
}

void DialogFresnel::DecideFunction(){
    if(operations == LE::Operations::GaussianBlur){
        LE::GaussianBlur(img, kernelSize->value(), sigma->value());
    }
    else if(operations == LE::Operations::PseudoFresnel){
        LE::PseudoFresnel(img, kernelSize->value(), sigma->value(), RGB(colorR->value(), colorG->value(), colorB->value()));
    }
}

void DialogFresnel::on_pushButton_pressed()
{
    DecideFunction();
    img->UpdateRender();
    QtLayers::UpdateRender(img, label);
}


void DialogFresnel::on_buttonBox_accepted()
{
    DecideFunction();
    LE::Apply(img);
    img->UpdateRender();
    QtLayers::UpdateRender(img, label);
    this->close();
}

void DialogFresnel::on_buttonBox_rejected()
{
    LE::Revert(img);
    img->UpdateRender();
    QtLayers::UpdateRender(img, label);
    this->close();
}
