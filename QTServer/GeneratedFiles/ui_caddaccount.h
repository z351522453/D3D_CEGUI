/********************************************************************************
** Form generated from reading UI file 'caddaccount.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CADDACCOUNT_H
#define UI_CADDACCOUNT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CAddAccount
{
public:
    QComboBox *comboBox_area;
    QComboBox *comboBox_server;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushButton_enter_acc;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_acc;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_psw;

    void setupUi(QDialog *CAddAccount)
    {
        if (CAddAccount->objectName().isEmpty())
            CAddAccount->setObjectName(QStringLiteral("CAddAccount"));
        CAddAccount->resize(393, 132);
        CAddAccount->setMinimumSize(QSize(393, 132));
        CAddAccount->setMaximumSize(QSize(393, 132));
        comboBox_area = new QComboBox(CAddAccount);
        comboBox_area->setObjectName(QStringLiteral("comboBox_area"));
        comboBox_area->setGeometry(QRect(50, 60, 101, 20));
        comboBox_server = new QComboBox(CAddAccount);
        comboBox_server->setObjectName(QStringLiteral("comboBox_server"));
        comboBox_server->setGeometry(QRect(260, 60, 121, 22));
        label_3 = new QLabel(CAddAccount);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(12, 60, 30, 21));
        label_3->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 127);"));
        label_4 = new QLabel(CAddAccount);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(210, 60, 41, 21));
        label_4->setStyleSheet(QLatin1String("\n"
"background-color: rgb(255, 0, 127);"));
        pushButton_enter_acc = new QPushButton(CAddAccount);
        pushButton_enter_acc->setObjectName(QStringLiteral("pushButton_enter_acc"));
        pushButton_enter_acc->setGeometry(QRect(150, 100, 75, 31));
        widget = new QWidget(CAddAccount);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 171, 22));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 0);"));

        horizontalLayout->addWidget(label);

        lineEdit_acc = new QLineEdit(widget);
        lineEdit_acc->setObjectName(QStringLiteral("lineEdit_acc"));

        horizontalLayout->addWidget(lineEdit_acc);

        widget1 = new QWidget(CAddAccount);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(210, 10, 171, 22));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget1);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 0);"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit_psw = new QLineEdit(widget1);
        lineEdit_psw->setObjectName(QStringLiteral("lineEdit_psw"));

        horizontalLayout_2->addWidget(lineEdit_psw);


        retranslateUi(CAddAccount);
        QObject::connect(pushButton_enter_acc, SIGNAL(clicked()), CAddAccount, SLOT(PushButton_Enter_Acc()));

        QMetaObject::connectSlotsByName(CAddAccount);
    } // setupUi

    void retranslateUi(QDialog *CAddAccount)
    {
        CAddAccount->setWindowTitle(QApplication::translate("CAddAccount", "\346\267\273\345\212\240\350\263\254\350\231\237", 0));
        comboBox_area->clear();
        comboBox_area->insertItems(0, QStringList()
         << QApplication::translate("CAddAccount", "\350\247\211\351\206\222\345\206\205\346\265\213\345\214\272", 0)
         << QApplication::translate("CAddAccount", "\345\220\210\344\275\234\344\275\223\351\252\214\345\214\272", 0)
        );
        comboBox_server->clear();
        comboBox_server->insertItems(0, QStringList()
         << QApplication::translate("CAddAccount", "\350\247\211\351\206\222\345\206\205\346\265\2131\346\234\215", 0)
         << QApplication::translate("CAddAccount", "\350\247\211\351\206\222\345\206\205\346\265\2132\346\234\215", 0)
         << QApplication::translate("CAddAccount", "\345\220\210\344\275\234\344\275\223\351\252\214\346\234\215", 0)
        );
        label_3->setText(QApplication::translate("CAddAccount", "\345\244\247\345\214\272:", 0));
        label_4->setText(QApplication::translate("CAddAccount", "\346\234\215\345\212\241\345\231\250:", 0));
        pushButton_enter_acc->setText(QApplication::translate("CAddAccount", "\347\241\256  \345\256\232", 0));
        label->setText(QApplication::translate("CAddAccount", "\350\264\246\345\217\267:", 0));
        label_2->setText(QApplication::translate("CAddAccount", "\345\257\206\347\240\201:", 0));
    } // retranslateUi

};

namespace Ui {
    class CAddAccount: public Ui_CAddAccount {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CADDACCOUNT_H
