#include <QVBoxLayout>

#include "mainwindow.h"
#include "dialoggaussian.h"
#include "dialogfresnel.h"
#include "ui_mainwindow.h"
#include "src/LayerEditor.hpp"
#include "dialogempty.h"
#include "dialogslider.h"
#include "qtlayers.h"
#include "colorcorrectiongraph.h"
#include "layerpanel.h"

#include <QFileDialog>
#include <QDir>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    imageLabel = ui->ImageLabel;
    console = ui->ConsoleInput;
    consoleLabel = ui->ConsoleOutput;
    scrollArea = ui->LayerScroll;
    img.UpdateRender();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    std::string path = QFileDialog::getOpenFileName(this, "Select an image", QDir::homePath(), "Images (*.ppm);;All Files (*.*)").toStdString();
    if(!path.empty()){
        img.Open(path);
        QtLayers::UpdateRender(&img, imageLabel);
        DrawLayers();
    }
}


void MainWindow::on_actionSave_triggered()
{
    std::string path = QFileDialog::getSaveFileName(this, "Select path", QDir::homePath(), "Images (*.ppm);;All Files (*.*)").toStdString();
    img.Save(path);
}


void MainWindow::on_actionNegativ_triggered()
{
    LE::Negativ(&img);
    QtLayers::UpdateRender(&img, imageLabel);
    DialogEmpty* e = new DialogEmpty(this, imageLabel, &img);
    e->show();
}


void MainWindow::on_actionResize_to_content_triggered()
{
    //create function to find the content size and move every layer to its corresponding position
    img.ScaleToContent();
    QtLayers::UpdateRender(&img, imageLabel);
}


void MainWindow::on_ConsoleInput_returnPressed()
{
    std::string command = console->text().toStdString();
    std::pair<bool, std::string> commandOutput = img.ConsoleInput(command);
    console->clear();
    if(commandOutput.first){
        QtLayers::UpdateRender(&img, imageLabel);
    }
    consoleLabel->setText(QString::fromStdString(commandOutput.second));
    DrawLayers();
}

void MainWindow::on_actionSaturation_triggered()
{
    LE::Saturation(&img);
    QtLayers::UpdateRender(&img, imageLabel);
    DialogSlider* e = new DialogSlider(this, imageLabel, &img, -1, 10, 2, LE::Operations::Saturation);
    e->show();
}


void MainWindow::on_actionContrast_triggered()
{
    LE::Contrast(&img);
    QtLayers::UpdateRender(&img, imageLabel);
    DialogSlider* e = new DialogSlider(this, imageLabel, &img, -127, 127, 0, LE::Operations::Contrast);
    e->show();
}


void MainWindow::on_actionBrightness_triggered()
{
    LE::Brightness(&img);
    QtLayers::UpdateRender(&img, imageLabel);
    DialogSlider* e = new DialogSlider(this, imageLabel, &img, -1, 1, 2, LE::Operations::Brightness);
    e->show();
}


void MainWindow::on_actionSobel_triggered()
{
    LE::Sobel(&img);
    QtLayers::UpdateRender(&img, imageLabel);
    DialogSlider* e = new DialogSlider(this, imageLabel, &img, -10, 10, 2, LE::Operations::Sobel);
    e->show();
}


void MainWindow::on_actionSobelOutline_triggered()
{
    LE::SobelOutline(&img);
    QtLayers::UpdateRender(&img, imageLabel);
    DialogSlider* e = new DialogSlider(this, imageLabel, &img, 0, 10, 2, LE::Operations::SobelOut);
    e->show();
}


void MainWindow::on_actionClose_triggered()
{
    img.Close();
    QtLayers::UpdateRender(&img, imageLabel);
}


void MainWindow::on_actionNoise_triggered()
{
    LE::Noise(&img);
    QtLayers::UpdateRender(&img, imageLabel);
    DialogSlider* e = new DialogSlider(this, imageLabel, &img, -1, 1, 2, LE::Operations::Noise);
    e->show();
}


void MainWindow::on_actionNoise_Gray_triggered()
{
    LE::NoiseG(&img);
    QtLayers::UpdateRender(&img, imageLabel);
    DialogSlider* e = new DialogSlider(this, imageLabel, &img, -1, 1, 2, LE::Operations::NoiseG);
    e->show();
}


void MainWindow::on_actionNoise_Multiplication_triggered()
{
    LE::NoiseGMult(&img);
    QtLayers::UpdateRender(&img, imageLabel);
    DialogSlider* e = new DialogSlider(this, imageLabel, &img, -5, 5, 2, LE::Operations::NoiseGMult);
    e->show();
}


void MainWindow::on_actionColor_correction_triggered()
{
    ColorCorrectionGraph* e = new ColorCorrectionGraph(this, &img, imageLabel);
    e->show();
}





void MainWindow::on_actionGaussian_triggered()
{
    DialogGaussian* e = new DialogGaussian(this, imageLabel, &img, LE::Operations::GaussianBlur);
    e->show();
}

void MainWindow::on_actionFresnel_triggered()
{
    DialogFresnel* e = new DialogFresnel(this, imageLabel, &img, LE::Operations::PseudoFresnel);
    e->show();
}

void MainWindow::DrawLayers(){
    QWidget* parent = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    parent->setLayout(layout);

    for(int i=0; i<img.GetLayersNumber(); i++){
        LayerPanel* child = new LayerPanel(parent, this, img.GetLayer(i), i);
        layout->addWidget(child);
    }
    scrollArea->setWidget(parent);
    parent->show();
}





void MainWindow::on_actionDefault_triggered()
{
    LE::Sharpening(&img);
    QtLayers::UpdateRender(&img, imageLabel);
    DialogEmpty* e = new DialogEmpty(this, imageLabel, &img);
    e->show();
}


void MainWindow::on_actionPrevitt_triggered()
{
    LE::Previtt(&img);
    QtLayers::UpdateRender(&img, imageLabel);
    DialogEmpty* e = new DialogEmpty(this, imageLabel, &img);
    e->show();
}

