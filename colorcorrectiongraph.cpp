#include "colorcorrectiongraph.h"
#include "ui_colorcorrectiongraph.h"
#include "pointholder.h"
#include "src/GraphLayer.hpp"
#include "qtlayers.h"

#include <iostream>
#include <QVBoxLayout>
#include <QImage>

#include "src/Layer.hpp"
#include "qtlayers.h"
#include "src/LayerEditor.hpp"

ColorCorrectionGraph::ColorCorrectionGraph(QWidget *parent, Image* _img, AspectRatioLabel* _label)
    : QDialog(parent)
    , ui(new Ui::ColorCorrectionGraph)
{
    ui->setupUi(this);
    scrollAreaR = ui->scrollAreaR;
    scrollAreaG = ui->scrollAreaG;
    scrollAreaB = ui->scrollAreaB;
    scrollAreaGlobal = ui->scrollAreaGlobal;

    labelR = ui->RedGraph;
    labelG = ui->GreenGraph;
    labelB = ui->BlueGraph;
    labelGlobal = ui->GlobalGraph;

    layerR = new Layer(vec::IVec2(256, 256));
    layerG = new Layer(vec::IVec2(256, 256));
    layerB = new Layer(vec::IVec2(256, 256));
    layerGlobal = new Layer(vec::IVec2(256, 256));

    DrawGraphR();
    DrawGraphG();
    DrawGraphB();
    DrawGraphGlobal();

    img = _img;
    label = _label;
}

ColorCorrectionGraph::~ColorCorrectionGraph()
{
    delete ui;
}

void ColorCorrectionGraph::on_PointsCounterR_valueChanged(int arg1)
{
    QWidget* parent = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    parent->setLayout(layout);

    for(int i=1; i<arg1+1; i++){
        std::cout<<"child added"<<std::endl;
        PointHolder* child = new PointHolder(parent, this, "R");
        layout->addWidget(child);
        QString name = "point"+QString::fromStdString(std::to_string(i));
        if(i<10){
            name+=" ";
        }
        child->name->setText(name);
    }
    scrollAreaR->setWidget(parent);
    parent->show();
}

void ColorCorrectionGraph::on_PointsCounterG_valueChanged(int arg1)
{
    QWidget* parent = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    parent->setLayout(layout);

    for(int i=1; i<arg1+1; i++){
        std::cout<<"child added"<<std::endl;
        PointHolder* child = new PointHolder(parent, this, "G");
        layout->addWidget(child);
        QString name = "point"+QString::fromStdString(std::to_string(i));
        if(i<10){
            name+=" ";
        }
        child->name->setText(name);
    }
    scrollAreaG->setWidget(parent);
    parent->show();
}

void ColorCorrectionGraph::on_PointsCounterB_valueChanged(int arg1)
{
    QWidget* parent = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    parent->setLayout(layout);

    for(int i=1; i<arg1+1; i++){
        std::cout<<"child added"<<std::endl;
        PointHolder* child = new PointHolder(parent, this, "B");
        layout->addWidget(child);
        QString name = "point"+QString::fromStdString(std::to_string(i));
        if(i<10){
            name+=" ";
        }
        child->name->setText(name);
    }
    scrollAreaB->setWidget(parent);
    parent->show();
}

void ColorCorrectionGraph::on_PointsCounterGlobal_valueChanged(int arg1)
{
    QWidget* parent = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    parent->setLayout(layout);

    for(int i=1; i<arg1+1; i++){
        std::cout<<"child added"<<std::endl;
        PointHolder* child = new PointHolder(parent, this, "Gl");
        layout->addWidget(child);
        QString name = "point"+QString::fromStdString(std::to_string(i));
        if(i<10){
            name+=" ";
        }
        child->name->setText(name);
    }
    scrollAreaGlobal->setWidget(parent);
    parent->show();
}

void ColorCorrectionGraph::on_previewButton_pressed()
{
    if(!useGlobals){
        std::vector<vec::IVec2> pointsR;
        std::vector<vec::IVec2> pointsG;
        std::vector<vec::IVec2> pointsB;

        QList<PointHolder*> pointHolders = scrollAreaR->findChildren<PointHolder*>();
        pointsR.push_back(vec::IVec2(0,0));
        pointsR.push_back(vec::IVec2(255, 255));
        for (PointHolder* holder : pointHolders){
            pointsR.push_back(holder->position);
        }
        pointHolders = scrollAreaG->findChildren<PointHolder*>();
        pointsG.push_back(vec::IVec2(0,0));
        pointsG.push_back(vec::IVec2(255, 255));
        for (PointHolder* holder : pointHolders){
            pointsG.push_back(holder->position);
        }
        pointHolders = scrollAreaB->findChildren<PointHolder*>();
        pointsB.push_back(vec::IVec2(0,0));
        pointsB.push_back(vec::IVec2(255, 255));
        for (PointHolder* holder : pointHolders){
            pointsB.push_back(holder->position);
        }
        LE::LagrangeCC(img, pointsR, pointsG, pointsB);
    }
    else{
        std::vector<vec::IVec2> points;
        QList<PointHolder*> pointHolders = scrollAreaGlobal->findChildren<PointHolder*>();
        points.push_back(vec::IVec2(0,0));
        points.push_back(vec::IVec2(255, 255));
        for (PointHolder* holder : pointHolders){
            points.push_back(holder->position);
        }
        LE::LagrangeCC(img, points, points, points);
    }
    QtLayers::UpdateRender(img, label);
}

void ColorCorrectionGraph::DrawGraphR(){
    std::vector<vec::IVec2> points;
    QList<PointHolder*> pointHolders = scrollAreaR->findChildren<PointHolder*>();
    points.push_back(vec::IVec2(0,0));
    points.push_back(vec::IVec2(255, 255));
    for (PointHolder* holder : pointHolders){
        points.push_back(holder->position);
    }

    layerR->Dealocate();
    layerR->layerMap = GraphLayer::DrawLagrange(points, 0, 255, RGB(255, 0, 0), true);

    QtLayers::UpdateRenderFromLayer(layerR, labelR);
}
void ColorCorrectionGraph::DrawGraphG(){
    std::vector<vec::IVec2> points;
    QList<PointHolder*> pointHolders = scrollAreaG->findChildren<PointHolder*>();
    points.push_back(vec::IVec2(0,0));
    points.push_back(vec::IVec2(255, 255));
    for (PointHolder* holder : pointHolders){
        points.push_back(holder->position);
    }

    layerG->Dealocate();
    layerG->layerMap = GraphLayer::DrawLagrange(points, 0, 255, RGB(0, 255, 0), true);

    QtLayers::UpdateRenderFromLayer(layerG, labelG);
}
void ColorCorrectionGraph::DrawGraphB(){
    std::vector<vec::IVec2> points;
    QList<PointHolder*> pointHolders = scrollAreaB->findChildren<PointHolder*>();
    points.push_back(vec::IVec2(0,0));
    points.push_back(vec::IVec2(255, 255));
    for (PointHolder* holder : pointHolders){
        points.push_back(holder->position);
    }

    layerB->Dealocate();
    layerB->layerMap = GraphLayer::DrawLagrange(points, 0, 255, RGB(0, 0, 255), true);

    QtLayers::UpdateRenderFromLayer(layerB, labelB);
}
void ColorCorrectionGraph::DrawGraphGlobal(){
    std::vector<vec::IVec2> points;
    QList<PointHolder*> pointHolders = scrollAreaGlobal->findChildren<PointHolder*>();
    points.push_back(vec::IVec2(0,0));
    points.push_back(vec::IVec2(255, 255));
    for (PointHolder* holder : pointHolders){
        points.push_back(holder->position);
    }

    layerGlobal->Dealocate();
    layerGlobal->layerMap = GraphLayer::DrawLagrange(points, 0, 255, RGB(0, 0, 0), true);

    QtLayers::UpdateRenderFromLayer(layerGlobal, labelGlobal);
}

void ColorCorrectionGraph::on_buttonBox_accepted()
{
    on_previewButton_pressed();
    LE::Apply(img);
}


void ColorCorrectionGraph::on_buttonBox_rejected()
{
    LE::Revert(img);
    QtLayers::UpdateRender(img, label);
}





void ColorCorrectionGraph::on_Globals_stateChanged(int arg1)
{
    std::cout<<arg1<<std::endl;
    if(arg1 != 0){
        useGlobals = true;
    }
    else useGlobals = false;
}

