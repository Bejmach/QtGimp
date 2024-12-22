#ifndef DIALOGSLIDER_H
#define DIALOGSLIDER_H

#include <QDialog>
#include <QLabel>
#include <QSlider>
#include <QDoubleSpinBox>

#include "src/Image.hpp"
#include "src/LayerEditor.hpp"
#include "aspectratiolabel.h"

namespace Ui {
class DialogSlider;
}

class DialogSlider : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSlider(QWidget *parent = nullptr, AspectRatioLabel* _imageLabel = nullptr, Image* img = nullptr, double min = 0, double max = 1, int decimals = 2, LE::Operations operation = LE::Operations::Undefined);
    ~DialogSlider();

    AspectRatioLabel* imageLabel;
    Image* img;
    Layer* layer;
    void* ImageOperation;
    LE::Operations Operation;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_SpinBox1_valueChanged(double arg1);

private:
    Ui::DialogSlider *ui;
};

#endif // DIALOGSLIDER_H
