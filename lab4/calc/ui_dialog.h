/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_06;
    QPushButton *pushButton_eq;
    QPushButton *pushButton_plus;
    QPushButton *pushButton_Div;
    QPushButton *pushButton_03;
    QPushButton *pushButton_02;
    QPushButton *pushButton_00;
    QPushButton *pushButton_07;
    QPushButton *pushButton_09;
    QPushButton *pushButton_01;
    QPushButton *pushButton_min;
    QPushButton *pushButton_04;
    QPushButton *pushButton_05;
    QPushButton *pushButton_clear;
    QPushButton *pushButton_sqrt;
    QPushButton *pushButton_08;
    QPushButton *pushButton_AC;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_first;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit_second;
    QLabel *label_eq;
    QLineEdit *lineEdit_result;
    QLabel *label_2;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(710, 502);
        gridLayoutWidget = new QWidget(Dialog);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(110, 330, 471, 120));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_06 = new QPushButton(gridLayoutWidget);
        pushButton_06->setObjectName(QStringLiteral("pushButton_06"));

        gridLayout->addWidget(pushButton_06, 2, 2, 1, 1);

        pushButton_eq = new QPushButton(gridLayoutWidget);
        pushButton_eq->setObjectName(QStringLiteral("pushButton_eq"));

        gridLayout->addWidget(pushButton_eq, 4, 2, 1, 1);

        pushButton_plus = new QPushButton(gridLayoutWidget);
        pushButton_plus->setObjectName(QStringLiteral("pushButton_plus"));

        gridLayout->addWidget(pushButton_plus, 1, 3, 1, 1);

        pushButton_Div = new QPushButton(gridLayoutWidget);
        pushButton_Div->setObjectName(QStringLiteral("pushButton_Div"));

        gridLayout->addWidget(pushButton_Div, 3, 3, 1, 1);

        pushButton_03 = new QPushButton(gridLayoutWidget);
        pushButton_03->setObjectName(QStringLiteral("pushButton_03"));

        gridLayout->addWidget(pushButton_03, 1, 2, 1, 1);

        pushButton_02 = new QPushButton(gridLayoutWidget);
        pushButton_02->setObjectName(QStringLiteral("pushButton_02"));

        gridLayout->addWidget(pushButton_02, 1, 1, 1, 1);

        pushButton_00 = new QPushButton(gridLayoutWidget);
        pushButton_00->setObjectName(QStringLiteral("pushButton_00"));

        gridLayout->addWidget(pushButton_00, 4, 1, 1, 1);

        pushButton_07 = new QPushButton(gridLayoutWidget);
        pushButton_07->setObjectName(QStringLiteral("pushButton_07"));

        gridLayout->addWidget(pushButton_07, 3, 0, 1, 1);

        pushButton_09 = new QPushButton(gridLayoutWidget);
        pushButton_09->setObjectName(QStringLiteral("pushButton_09"));

        gridLayout->addWidget(pushButton_09, 3, 2, 1, 1);

        pushButton_01 = new QPushButton(gridLayoutWidget);
        pushButton_01->setObjectName(QStringLiteral("pushButton_01"));

        gridLayout->addWidget(pushButton_01, 1, 0, 1, 1);

        pushButton_min = new QPushButton(gridLayoutWidget);
        pushButton_min->setObjectName(QStringLiteral("pushButton_min"));

        gridLayout->addWidget(pushButton_min, 2, 3, 1, 1);

        pushButton_04 = new QPushButton(gridLayoutWidget);
        pushButton_04->setObjectName(QStringLiteral("pushButton_04"));

        gridLayout->addWidget(pushButton_04, 2, 0, 1, 1);

        pushButton_05 = new QPushButton(gridLayoutWidget);
        pushButton_05->setObjectName(QStringLiteral("pushButton_05"));

        gridLayout->addWidget(pushButton_05, 2, 1, 1, 1);

        pushButton_clear = new QPushButton(gridLayoutWidget);
        pushButton_clear->setObjectName(QStringLiteral("pushButton_clear"));

        gridLayout->addWidget(pushButton_clear, 4, 0, 1, 1);

        pushButton_sqrt = new QPushButton(gridLayoutWidget);
        pushButton_sqrt->setObjectName(QStringLiteral("pushButton_sqrt"));

        gridLayout->addWidget(pushButton_sqrt, 4, 3, 1, 1);

        pushButton_08 = new QPushButton(gridLayoutWidget);
        pushButton_08->setObjectName(QStringLiteral("pushButton_08"));

        gridLayout->addWidget(pushButton_08, 3, 1, 1, 1);

        pushButton_AC = new QPushButton(gridLayoutWidget);
        pushButton_AC->setObjectName(QStringLiteral("pushButton_AC"));

        gridLayout->addWidget(pushButton_AC, 2, 4, 1, 1);

        horizontalLayoutWidget = new QWidget(Dialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(130, 110, 160, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_first = new QLineEdit(horizontalLayoutWidget);
        lineEdit_first->setObjectName(QStringLiteral("lineEdit_first"));

        horizontalLayout->addWidget(lineEdit_first);

        horizontalLayoutWidget_2 = new QWidget(Dialog);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(370, 110, 231, 80));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        lineEdit_second = new QLineEdit(horizontalLayoutWidget_2);
        lineEdit_second->setObjectName(QStringLiteral("lineEdit_second"));

        horizontalLayout_2->addWidget(lineEdit_second);

        label_eq = new QLabel(horizontalLayoutWidget_2);
        label_eq->setObjectName(QStringLiteral("label_eq"));

        horizontalLayout_2->addWidget(label_eq);

        lineEdit_result = new QLineEdit(horizontalLayoutWidget_2);
        lineEdit_result->setObjectName(QStringLiteral("lineEdit_result"));

        horizontalLayout_2->addWidget(lineEdit_result);

        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(300, 140, 67, 17));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", Q_NULLPTR));
        pushButton_06->setText(QApplication::translate("Dialog", "6", Q_NULLPTR));
        pushButton_eq->setText(QApplication::translate("Dialog", "=", Q_NULLPTR));
        pushButton_plus->setText(QApplication::translate("Dialog", "+", Q_NULLPTR));
        pushButton_Div->setText(QApplication::translate("Dialog", "/", Q_NULLPTR));
        pushButton_03->setText(QApplication::translate("Dialog", "3", Q_NULLPTR));
        pushButton_02->setText(QApplication::translate("Dialog", "2", Q_NULLPTR));
        pushButton_00->setText(QApplication::translate("Dialog", "0", Q_NULLPTR));
        pushButton_07->setText(QApplication::translate("Dialog", "7", Q_NULLPTR));
        pushButton_09->setText(QApplication::translate("Dialog", "9", Q_NULLPTR));
        pushButton_01->setText(QApplication::translate("Dialog", "1", Q_NULLPTR));
        pushButton_min->setText(QApplication::translate("Dialog", "-", Q_NULLPTR));
        pushButton_04->setText(QApplication::translate("Dialog", "4", Q_NULLPTR));
        pushButton_05->setText(QApplication::translate("Dialog", "5", Q_NULLPTR));
        pushButton_clear->setText(QApplication::translate("Dialog", "C", Q_NULLPTR));
        pushButton_sqrt->setText(QApplication::translate("Dialog", "*", Q_NULLPTR));
        pushButton_08->setText(QApplication::translate("Dialog", "8", Q_NULLPTR));
        pushButton_AC->setText(QApplication::translate("Dialog", "AC", Q_NULLPTR));
        label_eq->setText(QApplication::translate("Dialog", "=", Q_NULLPTR));
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
