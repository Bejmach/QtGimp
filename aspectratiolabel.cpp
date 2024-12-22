#include "aspectratiolabel.h"
#include "ui_aspectratiolabel.h"

#include <QImage>

AspectRatioLabel::AspectRatioLabel(QWidget *parent)
    : QLabel(parent)
    , ui(new Ui::AspectRatioLabel)
{
    ui->setupUi(this);

}

void AspectRatioLabel::resizeEvent(QResizeEvent *event){

    if(!pixmap() || pixmap().isNull()){
        QLabel::resizeEvent(event);
        return;
    }
    QSize scaledSize = CalculateAspectRatioSize(size());

    setPixmap(originalQPixmap->scaled(scaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QLabel::resizeEvent(event);
}

AspectRatioLabel::~AspectRatioLabel()
{
    delete ui;
    if(originalQPixmap!=nullptr){
        delete originalQPixmap;
    }
}

void AspectRatioLabel::UpdatePixmap(QImage image){
    originalQPixmap = new QPixmap(QPixmap::fromImage(image));
    QSize scaledSize = CalculateAspectRatioSize(size());

    setPixmap(originalQPixmap->scaled(scaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));

}

QSize AspectRatioLabel::CalculateAspectRatioSize(const QSize &availableSize){
    if (originalQPixmap->isNull())
        return QSize(0, 0);

    // Get the aspect ratio of the original pixmap
    int originalWidth = originalQPixmap->width();
    int originalHeight = originalQPixmap->height();
    double aspectRatio = static_cast<double>(originalWidth) / originalHeight;

    // Calculate the new size based on the available size
    int newWidth = availableSize.width();
    int newHeight = static_cast<int>(newWidth / aspectRatio);

    if (newHeight > availableSize.height()) {
        newHeight = availableSize.height();
        newWidth = static_cast<int>(newHeight * aspectRatio);
    }

    return QSize(newWidth, newHeight);
}
