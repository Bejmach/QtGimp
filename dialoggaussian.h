#ifndef DIALOGGAUSSIAN_H
#define DIALOGGAUSSIAN_H

#include <QDialog>
#include "src/Image.hpp"
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include "aspectratiolabel.h"
#include "src/LayerEditor.hpp"


namespace Ui {
class DialogGaussian;
}

class DialogGaussian : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGaussian(QWidget *parent = nullptr, AspectRatioLabel* label = nullptr, Image* img = nullptr, LE::Operations operation = LE::Operations::GaussianBlur);
    ~DialogGaussian();

    AspectRatioLabel* label;
    Image* img;

    QSpinBox* kernelSize;
    QDoubleSpinBox* sigma;

    LE::Operations operations;

private slots:
    void DecideFunction();
    void on_pushButton_pressed();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();


private:
    Ui::DialogGaussian *ui;
};

#endif // DIALOGGAUSSIAN_H
