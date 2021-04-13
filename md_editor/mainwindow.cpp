#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "translator.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

int MainWindow::tabStop=4;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,now_file_info("./")
    ,now_theme(getDefaultTheme())
{
    ui->setupUi(this);
    web_view = new QWebEngineView(ui->web_widget);
    QHBoxLayout *boxLayout=new QHBoxLayout();
    boxLayout->addWidget(web_view);
    ui->web_widget->setLayout(boxLayout);
    QFont font;
    QFontMetrics metrics(font);
    ui->md_text->setTabStopWidth(tabStop * metrics.width(' '));
    connect(ui->export_html,&QAction::triggered,this,&MainWindow::exportHtml);
    connect(ui->export_pdf,&QAction::triggered,this,&MainWindow::exportPdf);
    connect(ui->NewFile,&QAction::triggered,this,&MainWindow::newMdFile);
    connect(ui->OpenFile,&QAction::triggered,this,&MainWindow::openMdFile);
    connect(ui->SaveFile,&QAction::triggered,this,&MainWindow::saveMdFile);
    connect(ui->md_text,&QTextEdit::textChanged,this,&MainWindow::textToWebView);
    updateTitle();
}

MainWindow::~MainWindow()
{
    deleteTmpHtml();
    delete ui;
}

void MainWindow::updateTitle(bool changed)
{
    this->setWindowTitle(QString("M↓Editor&2<H>P (%1%2)").arg(now_file_info.fileName(),changed?"*":""));
}

void MainWindow::loadNewFile(QString filename)
{
    deleteTmpHtml();
    now_file_info=QFileInfo(filename);
    updateTitle();
    textToWebView();
}

void MainWindow::preCheckDefault()
{
    QDir main_dir("");
    if(!main_dir.exists("themes"))main_dir.mkdir("themes");
    QFileInfo theme_default_theme("themes/default.theme");
    if(!theme_default_theme.exists())QFile::copy(":/themes/default.theme","themes/default.theme");

}

void MainWindow::newMdFile()
{
    QString filename;
    filename=QFileDialog::getSaveFileName(nullptr,QString(),QString(),"markdown(*.md)");
    if(!filename.isNull()){
        QFile new_file(filename);
        if(!new_file.open(QFile::WriteOnly|QFile::Text)){
            QMessageBox::warning(this,tr("Error"),tr("save file error: &1").arg(new_file.errorString()));
            return;
        }
        loadNewFile(filename);
        updateTitle();
        ui->md_text->setText("");
    }
}

void MainWindow::openMdFile()
{
    QString filename=QFileDialog::getOpenFileName(nullptr,QString(),QString(),"md(*.md)");
    if(!filename.isNull()){
        QFile md_file(filename);
        if(!md_file.open(QFile::ReadOnly | QFile::Text)){
            QMessageBox::warning(this,tr("Error"),tr("save file error: &1").arg(md_file.errorString()));
            return;
        }
        loadNewFile(filename);
        QByteArray t = md_file.readAll();
        ui->md_text->setText(QString(t));
    }
}

void MainWindow::saveMdFile()
{
    QString filename;
    bool newfile=0;
    if(now_file_info.isDir())filename=QFileDialog::getSaveFileName(nullptr,QString(),QString(),"markdown(*.md)"),newfile=1;
    else filename=now_file_info.filePath();
    if(!filename.isNull()){
        QFile html_file(filename);
        if(!html_file.open(QFile::WriteOnly|QFile::Text)){
            QMessageBox::warning(this,tr("Error"),tr("save file error: &1").arg(html_file.errorString()));
            return;
        }
        if(newfile)loadNewFile(filename);
        updateTitle();
        QTextStream ofs(&html_file);
        ofs<<ui->md_text->toPlainText();
    }
}


void MainWindow::exportHtml()
{
    QString filename=QFileDialog::getSaveFileName(nullptr,QString(),QString(),"html(*.html)");
    if(!filename.isNull()){
        QFile html_file(filename);
        if(!html_file.open(QFile::WriteOnly|QFile::Text)){
            QMessageBox::warning(this,tr("Error"),tr("save file error: &1").arg(html_file.errorString()));
            return;
        }
        QTextStream ofs(&html_file);
        ofs<<getHtml(ui->md_text->toPlainText().toUtf8(),now_file_info.baseName(),now_theme);
    }
}

void MainWindow::exportPdf()
{
    QString filename=QFileDialog::getSaveFileName(nullptr,QString(),QString(),"pdf(*.pdf)");
    if(!filename.isNull()){
        QFile html_file(filename);
        if(!html_file.open(QFile::WriteOnly)){
            QMessageBox::warning(this,tr("Error"),tr("save file error: &1").arg(html_file.errorString()));
            return;
        }
        system(QString("wkhtmltopdf %1 %2").arg(now_file_info.path()+"/.tmp_html.html",now_file_info.path()+"/.tmp_pdf.pdf").toUtf8().constData());
        system(QString("mv %1 %2").arg(now_file_info.path()+"/.tmp_pdf.pdf",filename).toUtf8().constData());
    }
}

void MainWindow::textToWebView()
{
    updateTitle(1);
    QFile tmp_html_file(now_file_info.absolutePath()+"/.tmp_html.html");
    tmp_html_file.open(QFile::WriteOnly|QFile::Text);
    QTextStream ofs(&tmp_html_file);
    ofs<<getHtml(ui->md_text->toPlainText().toUtf8(),now_file_info.baseName(),now_theme);
    web_view->setUrl(QUrl("file:///"+now_file_info.absolutePath()+"/.tmp_html.html"));
}

void MainWindow::deleteTmpHtml()
{
    QFileInfo tmp_html_file(now_file_info.path()+"/.tmp_html.html");
    if(tmp_html_file.exists())tmp_html_file.dir().remove(tmp_html_file.fileName());
}

QString MainWindow::getDefaultTheme()
{
    preCheckDefault();
    QFile file("themes/default.theme");
    file.open(QFile::ReadOnly | QFile::Text);
    QByteArray t = file.readAll();
    return QString(t);
}


