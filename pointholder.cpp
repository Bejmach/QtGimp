#include "pointholder.h"
#include "ui_pointholder.h"

PointHolder::PointHolder(QWidget *parent, ColorCorrectionGraph* _graph, std::string _color)
    : QWidget(parent)
    , ui(new Ui::PointHolder)
{
    ui->setupUi(this);

    name = ui->Name;
    graph = _graph;
    color = _color;
}

PointHolder::~PointHolder()
{
    delete ui;
}

void PointHolder::on_PositionX_valueChanged(int arg1)
{
    position.x = arg1;
    if(color == "R"){
        graph->DrawGraphR();
    }
    else if(color == "G"){
        graph->DrawGraphG();
    }
    else if(color == "B"){
        graph->DrawGraphB();
    }
    else if(color == "Gl"){
        graph->DrawGraphGlobal();
    }
}


void PointHolder::on_PositionY_valueChanged(int arg1)
{
    position.y = arg1;
    if(color == "R"){
        graph->DrawGraphR();
    }
    else if(color == "G"){
        graph->DrawGraphG();
    }
    else if(color == "B"){
        graph->DrawGraphB();
    }
    else if(color == "Gl"){
        graph->DrawGraphGlobal();
    }
}

