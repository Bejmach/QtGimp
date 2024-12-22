#ifndef DIALOGEMPTY_H
#define DIALOGEMPTY_H

#include <QDialog>
#include <QLabel>

#include "src/Image.hpp"
#include "src/LayerEditor.hpp"
#include "aspectratiolabel.h"

namespace Ui {
class DialogEmpty;
}

class DialogEmpty : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEmpty(QWidget *parent = nullptr, AspectRatioLabel* _imageLabel = nullptr, Image* img = nullptr);
    ~DialogEmpty();

    AspectRatioLabel* imageLabel;
    Image* img;
    Layer* layer;
    LE::Operations Operators;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::DialogEmpty *ui;
};

#endif // DIALOGEMPTY_H
