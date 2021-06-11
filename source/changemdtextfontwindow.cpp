#include "changemdtextfontwindow.h"
#include "ui_changemdtextfontwindow.h"
#include <QtDebug>

ChangeMdTextFontWindow::ChangeMdTextFontWindow(QWidget *parent,QTextEdit *_md_text) :
    QWidget(parent),
    ui(new Ui::ChangeMdTextFontWindow),
    md_text(_md_text)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->font->setCurrentFont(md_text->font());
    ui->size->setValue(md_text->font().pointSize());
    connect(ui->font,&QFontComboBox::currentFontChanged,this,&ChangeMdTextFontWindow::change_font);
    connect(ui->size,SIGNAL(valueChanged(int)),this,SLOT(change_size(int)));
}

ChangeMdTextFontWindow::~ChangeMdTextFontWindow()
{
    delete ui;
}

void ChangeMdTextFontWindow::change_font(const QFont &f)
{
    md_text->setFont(QFont(ui->font->currentFont().family(),ui->size->value()));
}

void ChangeMdTextFontWindow::change_size(int size)
{
    md_text->setFont(QFont(ui->font->currentFont().family(),ui->size->value()));
}



