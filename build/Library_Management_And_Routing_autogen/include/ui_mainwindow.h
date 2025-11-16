/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QLabel *label;
    QLineEdit *searchID;
    QPushButton *Search;
    QLineEdit *searchout;
    QLabel *label_2;
    QLineEdit *Name;
    QLineEdit *ID;
    QPushButton *AddRecord;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 0, 201, 289));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        textEdit = new QTextEdit(widget);
        textEdit->setObjectName("textEdit");
        textEdit->setReadOnly(true);

        verticalLayout->addWidget(textEdit);

        label = new QLabel(widget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        searchID = new QLineEdit(widget);
        searchID->setObjectName("searchID");

        verticalLayout->addWidget(searchID);

        Search = new QPushButton(widget);
        Search->setObjectName("Search");

        verticalLayout->addWidget(Search);

        searchout = new QLineEdit(widget);
        searchout->setObjectName("searchout");
        searchout->setReadOnly(true);

        verticalLayout->addWidget(searchout);

        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        Name = new QLineEdit(widget);
        Name->setObjectName("Name");

        verticalLayout->addWidget(Name);

        ID = new QLineEdit(widget);
        ID->setObjectName("ID");

        verticalLayout->addWidget(ID);

        AddRecord = new QPushButton(widget);
        AddRecord->setObjectName("AddRecord");

        verticalLayout->addWidget(AddRecord);

        MainWindow->setCentralWidget(centralwidget);
        textEdit->raise();
        searchID->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        textEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:700;\">Library Records :</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", " Search by Book ID:", nullptr));
        searchID->setPlaceholderText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        Search->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        searchout->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "Add Record:", nullptr));
        Name->setText(QString());
        Name->setPlaceholderText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        ID->setText(QString());
        ID->setPlaceholderText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        AddRecord->setText(QCoreApplication::translate("MainWindow", "Add record", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
