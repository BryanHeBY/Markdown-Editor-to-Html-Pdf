/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *OpenFile;
    QAction *SaveFile;
    QAction *action_4;
    QAction *export_html;
    QAction *NewFile;
    QAction *export_pdf;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_2;
    QTextEdit *md_text;
    QWidget *web_widget;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("QTextEdit{\n"
"}"));
        OpenFile = new QAction(MainWindow);
        OpenFile->setObjectName(QString::fromUtf8("OpenFile"));
        SaveFile = new QAction(MainWindow);
        SaveFile->setObjectName(QString::fromUtf8("SaveFile"));
        action_4 = new QAction(MainWindow);
        action_4->setObjectName(QString::fromUtf8("action_4"));
        export_html = new QAction(MainWindow);
        export_html->setObjectName(QString::fromUtf8("export_html"));
        NewFile = new QAction(MainWindow);
        NewFile->setObjectName(QString::fromUtf8("NewFile"));
        export_pdf = new QAction(MainWindow);
        export_pdf->setObjectName(QString::fromUtf8("export_pdf"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        md_text = new QTextEdit(centralwidget);
        md_text->setObjectName(QString::fromUtf8("md_text"));
        md_text->setMaximumSize(QSize(782, 16777215));
        md_text->setStyleSheet(QString::fromUtf8("QTextEdit{\n"
"	padding:10px;\n"
"	font-size:16px;\n"
"}"));

        horizontalLayout_2->addWidget(md_text);

        web_widget = new QWidget(centralwidget);
        web_widget->setObjectName(QString::fromUtf8("web_widget"));

        horizontalLayout_2->addWidget(web_widget);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 1);

        horizontalLayout->addLayout(horizontalLayout_2);

        horizontalLayout->setStretch(0, 1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 28));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menu->addAction(NewFile);
        menu->addAction(OpenFile);
        menu->addAction(SaveFile);
        menu->addSeparator();
        menu->addAction(action_4);
        menu_3->addAction(export_html);
        menu_3->addAction(export_pdf);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        OpenFile->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266 &Open", nullptr));
#ifndef QT_NO_SHORTCUT
        OpenFile->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        SaveFile->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\346\226\207\344\273\266 &Save", nullptr));
#ifndef QT_NO_SHORTCUT
        SaveFile->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        action_4->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272 &Exit", nullptr));
        export_html->setText(QApplication::translate("MainWindow", "\345\257\274\345\207\272html", nullptr));
        NewFile->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\346\226\207\344\273\266 &New", nullptr));
#ifndef QT_NO_SHORTCUT
        NewFile->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_NO_SHORTCUT
        export_pdf->setText(QApplication::translate("MainWindow", "\345\257\274\345\207\272pdf", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QApplication::translate("MainWindow", "\344\270\273\351\242\230", nullptr));
        menu_3->setTitle(QApplication::translate("MainWindow", "\345\257\274\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
