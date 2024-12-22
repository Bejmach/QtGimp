#ifndef POINTHOLDER_H
#define POINTHOLDER_H

#include <QWidget>
#include <QLabel>
#include "src/Vector.hpp"
#include "colorcorrectiongraph.h"

namespace Ui {
class PointHolder;
}

class PointHolder : public QWidget
{
    Q_OBJECT

public:
    explicit PointHolder(QWidget *parent = nullptr, ColorCorrectionGraph* _graph = nullptr, std::string _color = "");
    ~PointHolder();

    QLabel* name;
    ColorCorrectionGraph* graph;

    vec::IVec2 position = vec::IVec2(0,0);
    std::string color;


private slots:
    void on_PositionX_valueChanged(int arg1);

    void on_PositionY_valueChanged(int arg1);

private:
    Ui::PointHolder *ui;
};

#endif // POINTHOLDER_H
