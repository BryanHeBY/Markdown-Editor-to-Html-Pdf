#ifndef CHANGEUSERDEFINEFILE_H
#define CHANGEUSERDEFINEFILE_H

#include <QWidget>

class MainWindow;

namespace Ui {
class ChangeUserDefineFile;
}

class ChangeUserDefineFile : public QWidget
{
    Q_OBJECT

public:
    explicit ChangeUserDefineFile(QWidget *parent, QString filePath, MainWindow *parent_window);
    ~ChangeUserDefineFile();
    void closeEvent ( QCloseEvent * e );

private:
    Ui::ChangeUserDefineFile *ui;
    MainWindow *_parent;
    QString FilePath;
};

#endif // CHANGEUSERDEFINEFILE_H
