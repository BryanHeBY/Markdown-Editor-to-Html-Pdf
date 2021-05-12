#include "changeuserdefinefile.h"
#include "ui_changeuserdefinefile.h"
#include "mainwindow.h"

ChangeUserDefineFile::ChangeUserDefineFile(QWidget *parent,QString filePath, MainWindow *parent_window) :
    QWidget(parent),
    ui(new Ui::ChangeUserDefineFile),
    _parent(parent_window),
    FilePath(filePath)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    QFile file(filePath);
    file.open(QFile::ReadOnly|QFile::Text);
    ui->UserDefineText->setPlainText(QString(file.readAll()));
}

ChangeUserDefineFile::~ChangeUserDefineFile()
{
    delete ui;
}

void ChangeUserDefineFile::closeEvent ( QCloseEvent * e )
{
    QFile file(FilePath);
    file.open(QFile::WriteOnly|QFile::Text);
    file.write(ui->UserDefineText->toPlainText().toUtf8());
    file.close();
    _parent->load_user_define();
    e->accept();
}
