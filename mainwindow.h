#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QScrollArea>

#include "src/Image.hpp"
#include "aspectratiolabel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QLineEdit* console;
    QLabel* consoleLabel;
    QScrollArea* scrollArea;
    AspectRatioLabel* imageLabel;
    Image img = Image(vec::IVec2(1920, 1080));
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void DrawLayers();

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionNegativ_triggered();

    void on_actionResize_to_content_triggered();

    void on_ConsoleInput_returnPressed();

    void on_actionSaturation_triggered();

    void on_actionContrast_triggered();

    void on_actionBrightness_triggered();

    void on_actionSobel_triggered();

    void on_actionSobelOutline_triggered();

    void on_actionClose_triggered();

    void on_actionNoise_triggered();

    void on_actionNoise_Gray_triggered();

    void on_actionNoise_Multiplication_triggered();

    void on_actionColor_correction_triggered();

    void on_actionGaussian_triggered();

    void on_actionFresnel_triggered();

    void on_actionDefault_triggered();

    void on_actionPrevitt_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
