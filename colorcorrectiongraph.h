#ifndef COLORCORRECTIONGRAPH_H
#define COLORCORRECTIONGRAPH_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <vector>

#include "src/Layer.hpp"
#include "aspectratiolabel.h"
#include "src/Image.hpp"
#include "aspectratiolabel.h"

namespace Ui {
class ColorCorrectionGraph;
}

class ColorCorrectionGraph : public QDialog
{
    Q_OBJECT

public:
    explicit ColorCorrectionGraph(QWidget *parent = nullptr, Image* _editedImage = nullptr, AspectRatioLabel* _imageLabel = nullptr);
    ~ColorCorrectionGraph();

    QScrollArea* scrollAreaR;
    QScrollArea* scrollAreaG;
    QScrollArea* scrollAreaB;
    QScrollArea* scrollAreaGlobal;

    AspectRatioLabel* labelR;
    AspectRatioLabel* labelG;
    AspectRatioLabel* labelB;
    AspectRatioLabel* labelGlobal;

    Layer* layerR;
    Layer* layerG;
    Layer* layerB;
    Layer* layerGlobal;

    void DrawGraphR();
    void DrawGraphG();
    void DrawGraphB();
    void DrawGraphGlobal();

    Image* img;

    AspectRatioLabel* label;

    bool useGlobals = false;


private slots:
    void on_PointsCounterR_valueChanged(int arg1);

    void on_PointsCounterG_valueChanged(int arg1);

    void on_PointsCounterB_valueChanged(int arg1);

    void on_previewButton_pressed();


    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_PointsCounterGlobal_valueChanged(int arg1);

    void on_Globals_stateChanged(int arg1);

private:
    Ui::ColorCorrectionGraph *ui;
};

#endif // COLORCORRECTIONGRAPH_H
