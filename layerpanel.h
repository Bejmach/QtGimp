#ifndef LAYERPANEL_H
#define LAYERPANEL_H

#include <QWidget>
#include <QPixmap>
#include <src/Layer.hpp>
#include "mainwindow.h"

namespace Ui {
class LayerPanel;
}

class LayerPanel : public QWidget
{
    Q_OBJECT

public:
    explicit LayerPanel(QWidget *parent = nullptr, MainWindow* window = nullptr, Layer* layer = nullptr, int id = 0);
    ~LayerPanel();

    MainWindow* window;

    int id;

private slots:
    void on_Select_pressed();

private:
    Ui::LayerPanel *ui;
};

#endif // LAYERPANEL_H
