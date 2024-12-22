#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QFileDialog>
#include <QString>

class FileDialog
{
public:
    FileDialog();
    static QString getFilePath(QWidget* parent = nullptr);
};

#endif // FILEDIALOG_H
