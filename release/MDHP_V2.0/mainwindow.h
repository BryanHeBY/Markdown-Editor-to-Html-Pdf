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
    MainWindow(QWidget *parent,QString open_file="");
    ~MainWindow();
    void updateTitle();
    void md_text_changed();
    void loadNewFile(QString);
    static void preCheckDefault();
    void newMdFile();
    void openMdFile();
    bool saveMdFile();
    void exportHtml();
    void exportPdf();
    void textToWebView();
    void deleteTmpHtml();
    void openHelp();
    void set_font();
    void set_theme();
    void load_user_define();
    void change_user_define();
    static QString getDefaultTheme();
    bool eventFilter(QObject *target, QEvent *event);
    void closeEvent ( QCloseEvent * e );
private:
    static int tabStop;
    bool file_changed;
    Ui::MainWindow *ui;
    QWebEngineView *web_view;
    QFileInfo now_file_info;
    QString now_theme;
};
#endif // MAINWINDOW_H
