#ifndef ASPECTRATIOLABEL_H
#define ASPECTRATIOLABEL_H

#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>
#include <qimage.h>

namespace Ui {
class AspectRatioLabel;
}

class AspectRatioLabel : public QLabel
{
    Q_OBJECT

public:
    explicit AspectRatioLabel(QWidget *parent = nullptr);
    ~AspectRatioLabel();
    void UpdatePixmap(QImage pixmap);

protected:
    void resizeEvent(QResizeEvent *event) override;

    QSize CalculateAspectRatioSize(const QSize &availableSize);

private:
    Ui::AspectRatioLabel *ui;

    QPixmap* originalQPixmap = nullptr;
};

#endif // ASPECTRATIOLABEL_H
