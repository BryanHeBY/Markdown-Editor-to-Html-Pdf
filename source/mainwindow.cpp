#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "translator.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QKeyEvent>
#include "changemdtextfontwindow.h"
#include "changeuserdefinefile.h"
#include "postpage.h"

int MainWindow::tabStop=4;

MainWindow::MainWindow(QWidget *parent,QString open_file)
    : QMainWindow(parent)
    ,file_changed(0)
    , ui(new Ui::MainWindow)
    ,now_file_info(QCoreApplication::applicationDirPath())
    ,now_theme(getDefaultTheme())
    ,evwidth({1,1})
{
    ui->setupUi(this);
    web_view = new QWebEngineView(this);
    //QHBoxLayout *boxLayout=new QHBoxLayout();
    //boxLayout->addWidget(web_view);
    ui->hlayout->addWidget(web_view);
    reload_evwidth();

    read_recent_file();
    add_recent_file_to_menu();

    QFont font;
    QFontMetrics metrics(font);
    ui->md_text->setTabStopWidth(tabStop * metrics.width(' '));
    ui->md_text->setAcceptRichText(false);

    connect(ui->V11,&QAction::triggered,this,[=](){set_evwidth({1,1});});
    connect(ui->V10,&QAction::triggered,this,[=](){set_evwidth({1,0});});
    connect(ui->V01,&QAction::triggered,this,[=](){set_evwidth({0,1});});
    connect(ui->V21,&QAction::triggered,this,[=](){set_evwidth({2,1});});
    connect(ui->V31,&QAction::triggered,this,[=](){set_evwidth({3,1});});

    connect(ui->export_link,&QAction::triggered,this,[=](){(new PostPage(NULL,getHtml(ui->md_text->toPlainText(),now_file_info.baseName(),now_theme)))->show();});

    connect(ui->new_Win,&QAction::triggered,this,[](){(new MainWindow(NULL,QString()))->show();});
    connect(ui->export_html,&QAction::triggered,this,&MainWindow::exportHtml);
    connect(ui->export_pdf,&QAction::triggered,this,&MainWindow::exportPdf);
    connect(ui->NewFile,&QAction::triggered,this,&MainWindow::newMdFile);
    connect(ui->OpenFile,&QAction::triggered,this,&MainWindow::openMdFile);
    connect(ui->SaveFile,&QAction::triggered,this,&MainWindow::saveMdFile);
    connect(ui->SaveAsFile,&QAction::triggered,this,&MainWindow::saveAsFile);
    connect(ui->Exit,&QAction::triggered,this,&MainWindow::close);
    connect(ui->handy_to_webview,&QAction::triggered,this,&MainWindow::textToWebView);
    connect(ui->undo,&QAction::triggered,ui->md_text,&QTextEdit::undo);
    connect(ui->redo,&QAction::triggered,ui->md_text,&QTextEdit::redo);
    connect(ui->open_help,&QAction::triggered,this,&MainWindow::openHelp);
    connect(ui->set_font,&QAction::triggered,this,&MainWindow::set_font);
    connect(ui->set_theme,&QAction::triggered,this,&MainWindow::set_theme);
    connect(ui->set_user_define,&QAction::triggered,this,&MainWindow::change_user_define);
    connect(ui->reload_user_define,&QAction::triggered,this,&MainWindow::load_user_define);
    connect(ui->md_text,&QTextEdit::textChanged,this,&MainWindow::md_text_changed);
    updateTitle();
    ui->md_text->installEventFilter(this);


    this->setAttribute(Qt::WA_DeleteOnClose);

    load_user_define();
    if(open_file.isEmpty())return;
    QFile new_md_file(open_file);
    if(!new_md_file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,tr("Error"),tr("Open file not found"));
        return;
    }
    loadNewFile(open_file);
    QByteArray t = new_md_file.readAll();
    ui->md_text->setPlainText(QString(t));
    textToWebView();
    file_changed=0;
    updateTitle();
    add_recent_file(open_file);
}

MainWindow::~MainWindow()
{
    deleteTmpHtml();
    delete web_view;
    delete ui;
}

void MainWindow::updateTitle()
{
    this->setWindowTitle(QString("M↓Editor&2<H>P (%1%2)").arg(now_file_info.isDir()?"untitle":now_file_info.fileName(),file_changed?"*":""));
}

void MainWindow::md_text_changed()
{
    file_changed=1;
    updateTitle();
}

void MainWindow::closeEvent ( QCloseEvent * e )
{
    if(!file_changed){
        e->accept();
        return;
    }
    auto reply=QMessageBox::question(this,
                                     tr("关闭窗口"),
                                     tr("该文件还未保存，你需要保存吗?"),
                                     QMessageBox::Cancel, QMessageBox::No,QMessageBox::Yes);
    if(reply == QMessageBox::Yes){
        if(!saveMdFile())e->ignore();
        else e->accept();
    }else if(reply==QMessageBox::No){
        e->accept();
    }
    else
        e->ignore();
}


void MainWindow::loadNewFile(QString filename)
{
    deleteTmpHtml();
    now_file_info=QFileInfo(filename);
}

void createfile(const QString &from_file_path,const QString &to_file_path){
    if(!QFileInfo(to_file_path).exists()){
        QFile from_file(from_file_path),to_file(to_file_path);
        from_file.open(QFile::ReadOnly|QFile::Text);
        to_file.open(QFile::WriteOnly|QFile::Text);
        to_file.write(from_file.readAll());
    }
}
void MainWindow::preCheckDefault()
{
    QDir main_dir(QCoreApplication::applicationDirPath());
    createfile(":/config/user_define.txt",QCoreApplication::applicationDirPath()+"/user_define.txt");
    if(!main_dir.exists("themes"))main_dir.mkdir("themes");
    createfile(":/themes/default.theme",QCoreApplication::applicationDirPath()+"/themes/default.theme");
    createfile(":/themes/ancient-book.theme",QCoreApplication::applicationDirPath()+"/themes/ancient-book.theme");

}

void MainWindow::newMdFile()
{
    if(file_changed){
        auto reply=QMessageBox::question(this,
                                         tr("Create new file"),
                                         tr("This file is not saved, do you want to save it?"),
                                         QMessageBox::Cancel, QMessageBox::No,QMessageBox::Yes);
        if(reply == QMessageBox::Yes){
            if(!saveMdFile())return;
        }else if(reply==QMessageBox::Cancel)
            return;
    }
    QString filename;
    filename=QFileDialog::getSaveFileName(nullptr,QString(),QString(),"markdown(*.md)");
    if(!filename.isNull()){
        QFile new_file(filename);
        if(!new_file.open(QFile::WriteOnly|QFile::Text)){
            QMessageBox::warning(this,tr("Error"),tr("save file error: %1").arg(new_file.errorString()));
            return;
        }
        loadNewFile(filename);
        updateTitle();
        ui->md_text->setPlainText("");
        textToWebView();
        file_changed=0;
        updateTitle();
        add_recent_file(filename);
    }
}

void MainWindow::openMdFile()
{
    if(file_changed){
        auto reply=QMessageBox::question(this,
                                         tr("Open new file"),
                                         tr("This file is not saved, do you want to save it?"),
                                         QMessageBox::Cancel, QMessageBox::No,QMessageBox::Yes);
        if(reply == QMessageBox::Yes){
            if(!saveMdFile())return;
        }else if(reply==QMessageBox::Cancel)
            return;
    }
    QString filename=QFileDialog::getOpenFileName(nullptr,QString(),QString(),"md(*.md)");
    if(!filename.isNull()){
        QFile md_file(filename);
        if(!md_file.open(QFile::ReadOnly | QFile::Text)){
            QMessageBox::warning(this,tr("Error"),tr("save file error: %1").arg(md_file.errorString()));
            return;
        }
        loadNewFile(filename);
        QByteArray t = md_file.readAll();
        ui->md_text->setPlainText(QString(t));
        textToWebView();
        file_changed=0;
        updateTitle();
        add_recent_file(filename);
    }
}

bool MainWindow::saveMdFile()
{
    QString filename;
    bool newfile=0;
    if(now_file_info.isDir())filename=QFileDialog::getSaveFileName(nullptr,QString(),QString(),"markdown(*.md)"),newfile=1;
    else filename=now_file_info.filePath();
    if(!filename.isNull()){
        QFile html_file(filename);
        if(!html_file.open(QFile::WriteOnly|QFile::Text)){
            QMessageBox::warning(this,tr("Error"),tr("save file error: %1").arg(html_file.errorString()));
            return 0;
        }
        if(newfile)loadNewFile(filename);
        file_changed=0;
        updateTitle();
        html_file.write(ui->md_text->toPlainText().toUtf8());
        add_recent_file(filename);
        return 1;
    }
    return 0;
}

bool MainWindow::saveAsFile()
{
    QString filename(QFileDialog::getSaveFileName(nullptr,QString(),QString(),"markdown(*.md)"));
    if(!filename.isNull()){
        QFile html_file(filename);
        if(!html_file.open(QFile::WriteOnly|QFile::Text)){
            QMessageBox::warning(this,tr("Error"),tr("save file error: %1").arg(html_file.errorString()));
            return 0;
        }
        loadNewFile(filename);
        file_changed=0;
        updateTitle();
        html_file.write(ui->md_text->toPlainText().toUtf8());
        add_recent_file(filename);
        return 1;
    }
    return 0;
}

void MainWindow::exportHtml()
{
    QString filename=QFileDialog::getSaveFileName(nullptr,QString(),QString(),"html(*.html)");
    if(!filename.isNull()){
        QFile html_file(filename);
        if(!html_file.open(QFile::WriteOnly|QFile::Text)){
            QMessageBox::warning(this,tr("Error"),tr("save file error: %1").arg(html_file.errorString()));
            return;
        }
        html_file.write(getHtml(ui->md_text->toPlainText(),now_file_info.baseName(),now_theme).toUtf8());
    }
}

void MainWindow::exportPdf()
{
    textToWebView();
    QString filename=QFileDialog::getSaveFileName(nullptr,QString(),QString(),"pdf(*.pdf)");
    if(!filename.isNull()){
        QFile html_file(filename);
        if(!html_file.open(QFile::WriteOnly)){
            QMessageBox::warning(this,tr("Error"),tr("save file error: &1").arg(html_file.errorString()));
            return;
        }
#ifdef Q_OS_LINUX
        system(QString("wkhtmltopdf '%2' '%3'").arg(now_file_info.path()+"/.tmp_html.html",filename).toUtf8().constData());
#endif
#ifdef Q_OS_WIN
        QProcess process;
        process.start(QString("\"%1/wkhtmltopdf.exe\" --enable-local-file-access \"%2\" \"%3\"").arg(QCoreApplication::applicationDirPath(),now_file_info.path()+"/.tmp_html.html",filename));
        process.waitForFinished();
#endif
    }
}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if(target == ui->md_text)
    {
        if(event->type() == QEvent::KeyPress){
            QKeyEvent *k = static_cast<QKeyEvent *>(event);
            if(k->modifiers()==Qt::ShiftModifier&&k->key() == Qt::Key_Return)
            {
                ui->md_text->textCursor().insertText("<br>\n");
                textToWebView();
                return true;
            }else if(k->key() == Qt::Key_Return)
            {
                 ui->md_text->textCursor().insertText("\n");
                 textToWebView();
                 return true;
            }else if(k->modifiers()==Qt::ControlModifier&&k->key() == Qt::Key_U)
            {
                  ui->md_text->textCursor().insertText("<u></u>");
                  for(int i=0;i<4;i++)ui->md_text->moveCursor(QTextCursor::Left);
                  return true;
            }

        }
    }
    return QWidget::eventFilter(target,event);
}


void MainWindow::textToWebView()
{
    QFile tmp_html_file(now_file_info.absolutePath()+"/.tmp_html.html");
    tmp_html_file.open(QFile::WriteOnly|QFile::Text);
    tmp_html_file.write(getHtml(ui->md_text->toPlainText(),now_file_info.baseName(),now_theme).toUtf8());
    if(web_view)web_view->setUrl(QUrl("file:///"+now_file_info.absolutePath()+"/.tmp_html.html"));
    ui->md_text->setFocus();
}

void MainWindow::deleteTmpHtml()
{
    QFileInfo tmp_html_file(now_file_info.path()+"/.tmp_html.html");
    if(tmp_html_file.exists())tmp_html_file.dir().remove(tmp_html_file.fileName());
}

void MainWindow::openHelp()
{
    MainWindow *new_open_file=new MainWindow(NULL,QCoreApplication::applicationDirPath()+"/README/README.md");
    new_open_file->show();
}

void MainWindow::set_font()
{
    (new ChangeMdTextFontWindow(NULL,ui->md_text))->show();
}

void MainWindow::set_theme()
{
    QString filename=QFileDialog::getOpenFileName(nullptr,QString(),QCoreApplication::applicationDirPath()+"/themes","theme(*.theme)");
    if(!filename.isNull()){
        QFile theme_file(filename);
        if(!theme_file.open(QFile::ReadOnly | QFile::Text)){
            QMessageBox::warning(this,tr("Error"),tr("save file error: &1").arg(theme_file.errorString()));
            return;
        }
        QByteArray t = theme_file.readAll();
        now_theme=QString(t);
        textToWebView();
    }
}

bool MainWindow::load_user_define()
{
    QFile file(QCoreApplication::applicationDirPath()+"/user_define.txt");
    file.open(QFile::ReadOnly | QFile::Text);
    if(set_user_define(QString(file.readAll())))return true;
    textToWebView();
    return false;
}

void MainWindow::change_user_define(){(new ChangeUserDefineFile(NULL,QCoreApplication::applicationDirPath()+"/user_define.txt",this))->show();}

void MainWindow::reload_evwidth(){
    ui->hlayout->setStretch(0,evwidth.first);
    ui->hlayout->setStretch(1,evwidth.second);
}

void MainWindow::set_evwidth(const QPair<int, int> &v)
{
    evwidth=v;
    reload_evwidth();
}



void MainWindow::add_recent_file(const QString new_file)
{
    read_recent_file();
    if(QFileInfo(new_file).isFile()){
        for(auto i=recent_file_list.begin();i!=recent_file_list.end();){
            if(*i==new_file)i=recent_file_list.erase(i);
            else i++;
        }
        recent_file_list.push_front(new_file);
        if(recent_file_list.size()>recent_file_list_num)recent_file_list.pop_back();
    }
    add_recent_file_to_menu();
    write_recent_file();
}

void MainWindow::add_recent_file_to_menu()
{
    ui->recent_files->clear();
    for(const QString &str:recent_file_list){
        QAction *file_item=new QAction();
        file_item->setText(str);
        ui->recent_files->addAction(file_item);
        connect(file_item,&QAction::triggered,this,[=](){(new MainWindow(NULL,str))->show();});
    }
    ui->recent_files->addSeparator();
    QAction *clear_recent=new QAction();
    clear_recent->setText("清空最近文件列表");
    connect(clear_recent,&QAction::triggered,this,&MainWindow::clear_recent_file);
    ui->recent_files->addAction(clear_recent);
}

void MainWindow::read_recent_file()
{
    recent_file_list.clear();
    QFile file_list(QCoreApplication::applicationDirPath()+"/recent_file_list.txt");
    if(file_list.open(QFile::ReadOnly|QFile::Text)){
        QString str(file_list.readAll());
        QStringList lines=str.split(QRegularExpression("\\r?\\n"));
        for(const auto &line:lines)if(QFileInfo(line).isFile()){
            recent_file_list.push_back(line);
        }
    }
}

void MainWindow::write_recent_file()
{
    QString str;
    for(const auto &file:recent_file_list)str+=file+'\n';
    QFile file_list_new(QCoreApplication::applicationDirPath()+"/recent_file_list.txt");
    if(file_list_new.open(QFile::WriteOnly|QFile::Text)){
        file_list_new.write(str.toUtf8());
    }
}

void MainWindow::clear_recent_file()
{
    recent_file_list.clear();
    add_recent_file_to_menu();
    write_recent_file();
}


QString MainWindow::getDefaultTheme()
{
    preCheckDefault();
    QFile file(QCoreApplication::applicationDirPath()+"/themes/default.theme");
    file.open(QFile::ReadOnly | QFile::Text);
    QByteArray t = file.readAll();
    return QString(t);
}


