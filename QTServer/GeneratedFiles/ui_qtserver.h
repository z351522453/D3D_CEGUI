/********************************************************************************
** Form generated from reading UI file 'qtserver.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTSERVER_H
#define UI_QTSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>
#include "cmytablewidget.h"

QT_BEGIN_NAMESPACE

class Ui_QTServerClass
{
public:
    QAction *actionAddAccount;
    QAction *actionOption;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    CMyTableWidget *tableWidget;
    QMenuBar *menuBar;
    QMenu *menu;

    void setupUi(QMainWindow *QTServerClass)
    {
        if (QTServerClass->objectName().isEmpty())
            QTServerClass->setObjectName(QStringLiteral("QTServerClass"));
        QTServerClass->resize(526, 354);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QTServerClass->sizePolicy().hasHeightForWidth());
        QTServerClass->setSizePolicy(sizePolicy);
        actionAddAccount = new QAction(QTServerClass);
        actionAddAccount->setObjectName(QStringLiteral("actionAddAccount"));
        actionOption = new QAction(QTServerClass);
        actionOption->setObjectName(QStringLiteral("actionOption"));
        centralWidget = new QWidget(QTServerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        tableWidget = new CMyTableWidget(centralWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->horizontalHeader()->setCascadingSectionResizes(true);
        tableWidget->horizontalHeader()->setDefaultSectionSize(100);
        tableWidget->horizontalHeader()->setMinimumSectionSize(27);
        tableWidget->verticalHeader()->setCascadingSectionResizes(false);
        tableWidget->verticalHeader()->setDefaultSectionSize(30);
        tableWidget->verticalHeader()->setMinimumSectionSize(21);

        horizontalLayout->addWidget(tableWidget);

        QTServerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QTServerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 526, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        QTServerClass->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actionAddAccount);
        menu->addAction(actionOption);

        retranslateUi(QTServerClass);

        QMetaObject::connectSlotsByName(QTServerClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTServerClass)
    {
        QTServerClass->setWindowTitle(QApplication::translate("QTServerClass", "Server", 0));
        actionAddAccount->setText(QApplication::translate("QTServerClass", "\346\267\273\345\212\240\350\263\254\350\231\237", 0));
        actionOption->setText(QApplication::translate("QTServerClass", "\345\261\254\346\200\247\350\250\255\347\275\256", 0));
        menu->setTitle(QApplication::translate("QTServerClass", "\350\256\276\347\275\256", 0));
    } // retranslateUi

};

namespace Ui {
    class QTServerClass: public Ui_QTServerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTSERVER_H