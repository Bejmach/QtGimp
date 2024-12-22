#ifndef DIALOGFRESNEL_H
#define DIALOGFRESNEL_H

#include <QDialog>
#include "src/Image.hpp"
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include "aspectratiolabel.h"
#include "src/LayerEditor.hpp"


namespace Ui {
class DialogFresnel;
}

class DialogFresnel : public QDialog
{
    Q_OBJECT

public:
    explicit DialogFresnel(QWidget *parent = nullptr, AspectRatioLabel* label = nullptr, Image* img = nullptr, LE::Operations operation = LE::Operations::GaussianBlur);
    ~DialogFresnel();

    AspectRatioLabel* label;
    Image* img;

    QSpinBox* kernelSize;
    QDoubleSpinBox* sigma;

    LE::Operations operations;

    QSpinBox* colorR;
    QSpinBox* colorG;
    QSpinBox* colorB;

private slots:
    void DecideFunction();
    void on_pushButton_pressed();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();


private:
    Ui::DialogFresnel *ui;
};

#endif // DIALOGFRESNEL_H
