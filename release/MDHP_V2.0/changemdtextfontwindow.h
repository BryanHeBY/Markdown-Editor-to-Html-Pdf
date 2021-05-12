#ifndef CHANGEMDTEXTFONTWINDOW_H
#define CHANGEMDTEXTFONTWINDOW_H

#include <QWidget>
#include <QPlainTextEdit>

namespace Ui {
class ChangeMdTextFontWindow;
}

class ChangeMdTextFontWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChangeMdTextFontWindow(QWidget *parent,QTextEdit *_md_text);
    ~ChangeMdTextFontWindow();
public slots:
    void change_font(const QFont &f);
    void change_size(int size);

private:
    Ui::ChangeMdTextFontWindow *ui;
    QTextEdit *md_text;
};

#endif // CHANGEMDTEXTFONTWINDOW_H
