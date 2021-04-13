#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QFileInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateTitle(bool changed=0);
    void loadNewFile(QString);
    static void preCheckDefault();
    void newMdFile();
    void openMdFile();
    void saveMdFile();
    void exportHtml();
    void exportPdf();
    void textToWebView();
    void deleteTmpHtml();
    static QString getDefaultTheme();
private:
    static int tabStop;
    Ui::MainWindow *ui;
    QWebEngineView *web_view;
    QFileInfo now_file_info;
    QString now_theme;
};
#endif // MAINWINDOW_H
