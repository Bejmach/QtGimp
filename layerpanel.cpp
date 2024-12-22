#include "layerpanel.h"
#include "ui_layerpanel.h"
#include "qtlayers.h"

LayerPanel::LayerPanel(QWidget *parent, MainWindow* _window, Layer* layer, int _id)
    : QWidget(parent)
    , ui(new Ui::LayerPanel)
{
    ui->setupUi(this);
    QtLayers::UpdateRenderFromLayer(layer, ui->LayerPreview);
    ui->Name->setText(QString::fromStdString(std::to_string(id)));

    window = _window;

    id = _id;
}

LayerPanel::~LayerPanel()
{
    delete ui;
}

void LayerPanel::on_Select_pressed()
{
    window->img.focusedLayerId = id;
}

