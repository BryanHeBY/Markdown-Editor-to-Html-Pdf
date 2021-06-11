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
    bool saveAsFile();
    void exportHtml();
    void exportPdf();
    void textToWebView();
    void deleteTmpHtml();
    void openHelp();
    void set_font();
    void set_theme();
    bool load_user_define();
    void change_user_define();
    void reload_evwidth();
    void set_evwidth(const QPair<int,int> &v);
    void add_recent_file(const QString new_file);
    void add_recent_file_to_menu();
    void read_recent_file();
    void write_recent_file();
    void clear_recent_file();
    void change_original_text();
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
    QPair<int,int> evwidth;
    const int recent_file_list_num=8;
    QList<QString> recent_file_list;
};
#endif // MAINWINDOW_H
