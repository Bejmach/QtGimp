#include "dialogempty.h"
#include "ui_dialogempty.h"
#include "src/Image.hpp"
#include "qtlayers.h"
#include "src/LayerEditor.hpp"

#include <QLabel>


DialogEmpty::DialogEmpty(QWidget *parent, AspectRatioLabel* _imageLabel, Image* _img)
    : QDialog(parent)
    , ui(new Ui::DialogEmpty)
{
    ui->setupUi(this);

    img = _img;
    imageLabel = _imageLabel;
    layer = img->GetLayer(img->focusedLayerId);
}

DialogEmpty::~DialogEmpty()
{
    delete ui;
}

void DialogEmpty::on_buttonBox_accepted()
{
    LE::Apply(img);
    img->UpdateRender();
    QtLayers::UpdateRender(img, imageLabel);
    this->close();
}


void DialogEmpty::on_buttonBox_rejected()
{
    LE::Revert(img);
    img->UpdateRender();
    QtLayers::UpdateRender(img, imageLabel);
    this->close();
}

