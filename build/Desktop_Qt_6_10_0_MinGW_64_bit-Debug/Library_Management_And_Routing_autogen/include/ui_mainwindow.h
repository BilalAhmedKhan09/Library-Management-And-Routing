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
#include <QtWidgets/QHBoxLayout>
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
    QWidget *Graphwidget;
    QWidget *Selectionwidget;
    QWidget *layoutWidget;
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
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *textEdit_2;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *Nname;
    QPushButton *AddNode;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout;
    QLabel *label_6;
    QLineEdit *N1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_7;
    QLineEdit *N2;
    QPushButton *AddEdge;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(759, 605);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        Graphwidget = new QWidget(centralwidget);
        Graphwidget->setObjectName("Graphwidget");
        Graphwidget->setGeometry(QRect(280, -30, 451, 591));
        Graphwidget->setMinimumSize(QSize(451, 591));
        Selectionwidget = new QWidget(centralwidget);
        Selectionwidget->setObjectName("Selectionwidget");
        Selectionwidget->setGeometry(QRect(0, 0, 271, 561));
        layoutWidget = new QWidget(Selectionwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(0, 0, 271, 289));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        textEdit = new QTextEdit(layoutWidget);
        textEdit->setObjectName("textEdit");
        textEdit->setReadOnly(true);

        verticalLayout->addWidget(textEdit);

        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label, 0, Qt::AlignmentFlag::AlignHCenter);

        searchID = new QLineEdit(layoutWidget);
        searchID->setObjectName("searchID");

        verticalLayout->addWidget(searchID);

        Search = new QPushButton(layoutWidget);
        Search->setObjectName("Search");

        verticalLayout->addWidget(Search);

        searchout = new QLineEdit(layoutWidget);
        searchout->setObjectName("searchout");
        searchout->setReadOnly(true);

        verticalLayout->addWidget(searchout);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2, 0, Qt::AlignmentFlag::AlignHCenter);

        Name = new QLineEdit(layoutWidget);
        Name->setObjectName("Name");

        verticalLayout->addWidget(Name);

        ID = new QLineEdit(layoutWidget);
        ID->setObjectName("ID");

        verticalLayout->addWidget(ID);

        AddRecord = new QPushButton(layoutWidget);
        AddRecord->setObjectName("AddRecord");

        verticalLayout->addWidget(AddRecord);

        layoutWidget1 = new QWidget(Selectionwidget);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(0, 300, 271, 251));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        textEdit_2 = new QTextEdit(layoutWidget1);
        textEdit_2->setObjectName("textEdit_2");
        textEdit_2->setReadOnly(true);

        verticalLayout_2->addWidget(textEdit_2);

        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName("label_4");

        verticalLayout_2->addWidget(label_4, 0, Qt::AlignmentFlag::AlignHCenter);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName("label_3");

        horizontalLayout_2->addWidget(label_3);

        Nname = new QLineEdit(layoutWidget1);
        Nname->setObjectName("Nname");

        horizontalLayout_2->addWidget(Nname);


        verticalLayout_2->addLayout(horizontalLayout_2);

        AddNode = new QPushButton(layoutWidget1);
        AddNode->setObjectName("AddNode");

        verticalLayout_2->addWidget(AddNode);

        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName("label_5");

        verticalLayout_2->addWidget(label_5, 0, Qt::AlignmentFlag::AlignHCenter);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_6 = new QLabel(layoutWidget1);
        label_6->setObjectName("label_6");

        horizontalLayout->addWidget(label_6);

        N1 = new QLineEdit(layoutWidget1);
        N1->setObjectName("N1");

        horizontalLayout->addWidget(N1);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_7 = new QLabel(layoutWidget1);
        label_7->setObjectName("label_7");

        horizontalLayout_3->addWidget(label_7);

        N2 = new QLineEdit(layoutWidget1);
        N2->setObjectName("N2");

        horizontalLayout_3->addWidget(N2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        AddEdge = new QPushButton(layoutWidget1);
        AddEdge->setObjectName("AddEdge");

        verticalLayout_2->addWidget(AddEdge);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 759, 22));
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
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:700;\">Library Records :</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", " Search by Book ID:", nullptr));
        searchID->setPlaceholderText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        Search->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        searchout->setText(QString());
        searchout->setPlaceholderText(QCoreApplication::translate("MainWindow", "Book Name", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Add Record:", nullptr));
        Name->setText(QString());
        Name->setPlaceholderText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        ID->setText(QString());
        ID->setPlaceholderText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        AddRecord->setText(QCoreApplication::translate("MainWindow", "Add record", nullptr));
        textEdit_2->setMarkdown(QCoreApplication::translate("MainWindow", "**Graph Creation :**\n"
"\n"
"", nullptr));
        textEdit_2->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:6px; margin-bottom:6px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:700;\">Graph Creation :</span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Node Creation:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Name : ", nullptr));
        AddNode->setText(QCoreApplication::translate("MainWindow", "Add Node", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Edge Creation:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Node 1", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Node 2", nullptr));
        AddEdge->setText(QCoreApplication::translate("MainWindow", "Add Edge", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
