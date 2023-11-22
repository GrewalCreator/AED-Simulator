/********************************************************************************
** Form generated from reading UI file 'aedwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AEDWINDOW_H
#define UI_AEDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AEDWindow
{
public:
    QWidget *centralwidget;
    QFrame *frame;
    QLabel *step1_image;
    QLabel *step2_image;
    QLabel *step3_image;
    QLabel *step4_image;
    QLabel *step5_image;
    QLabel *step6_image;
    QPushButton *power_button;
    QTextBrowser *instruction_console;
    QLCDNumber *heartRate_LCD;
    QLabel *heartRate_label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *shock_button;
    QLabel *padsPlacement_image;
    QPushButton *statusLight_image;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AEDWindow)
    {
        if (AEDWindow->objectName().isEmpty())
            AEDWindow->setObjectName(QString::fromUtf8("AEDWindow"));
        AEDWindow->resize(969, 528);
        centralwidget = new QWidget(AEDWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 951, 471));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        step1_image = new QLabel(frame);
        step1_image->setObjectName(QString::fromUtf8("step1_image"));
        step1_image->setGeometry(QRect(20, 10, 121, 71));
        step1_image->setAutoFillBackground(true);
        step1_image->setAlignment(Qt::AlignCenter);
        step2_image = new QLabel(frame);
        step2_image->setObjectName(QString::fromUtf8("step2_image"));
        step2_image->setGeometry(QRect(180, 10, 121, 71));
        step2_image->setAutoFillBackground(true);
        step2_image->setAlignment(Qt::AlignCenter);
        step3_image = new QLabel(frame);
        step3_image->setObjectName(QString::fromUtf8("step3_image"));
        step3_image->setGeometry(QRect(340, 10, 121, 71));
        step3_image->setAutoFillBackground(true);
        step3_image->setAlignment(Qt::AlignCenter);
        step4_image = new QLabel(frame);
        step4_image->setObjectName(QString::fromUtf8("step4_image"));
        step4_image->setGeometry(QRect(490, 10, 121, 71));
        step4_image->setAutoFillBackground(true);
        step4_image->setAlignment(Qt::AlignCenter);
        step5_image = new QLabel(frame);
        step5_image->setObjectName(QString::fromUtf8("step5_image"));
        step5_image->setGeometry(QRect(650, 10, 121, 71));
        step5_image->setAutoFillBackground(true);
        step5_image->setAlignment(Qt::AlignCenter);
        step6_image = new QLabel(frame);
        step6_image->setObjectName(QString::fromUtf8("step6_image"));
        step6_image->setGeometry(QRect(810, 10, 121, 71));
        step6_image->setAutoFillBackground(true);
        step6_image->setAlignment(Qt::AlignCenter);
        power_button = new QPushButton(frame);
        power_button->setObjectName(QString::fromUtf8("power_button"));
        power_button->setGeometry(QRect(20, 140, 51, 41));
        instruction_console = new QTextBrowser(frame);
        instruction_console->setObjectName(QString::fromUtf8("instruction_console"));
        instruction_console->setGeometry(QRect(240, 140, 311, 111));
        heartRate_LCD = new QLCDNumber(frame);
        heartRate_LCD->setObjectName(QString::fromUtf8("heartRate_LCD"));
        heartRate_LCD->setGeometry(QRect(560, 180, 131, 51));
        heartRate_label = new QLabel(frame);
        heartRate_label->setObjectName(QString::fromUtf8("heartRate_label"));
        heartRate_label->setGeometry(QRect(550, 140, 161, 31));
        heartRate_label->setAlignment(Qt::AlignCenter);
        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(40, 90, 83, 25));
        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(200, 90, 83, 25));
        pushButton_3 = new QPushButton(frame);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(360, 90, 83, 25));
        pushButton_4 = new QPushButton(frame);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(510, 90, 83, 25));
        pushButton_5 = new QPushButton(frame);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(670, 90, 83, 25));
        pushButton_6 = new QPushButton(frame);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(830, 90, 83, 25));
        shock_button = new QPushButton(frame);
        shock_button->setObjectName(QString::fromUtf8("shock_button"));
        shock_button->setGeometry(QRect(280, 350, 341, 91));
        padsPlacement_image = new QLabel(frame);
        padsPlacement_image->setObjectName(QString::fromUtf8("padsPlacement_image"));
        padsPlacement_image->setGeometry(QRect(720, 290, 201, 101));
        padsPlacement_image->setAutoFillBackground(true);
        padsPlacement_image->setAlignment(Qt::AlignCenter);
        statusLight_image = new QPushButton(frame);
        statusLight_image->setObjectName(QString::fromUtf8("statusLight_image"));
        statusLight_image->setGeometry(QRect(30, 320, 101, 41));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 290, 62, 17));
        label->setAlignment(Qt::AlignCenter);
        AEDWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AEDWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 969, 22));
        AEDWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(AEDWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        AEDWindow->setStatusBar(statusbar);

        retranslateUi(AEDWindow);

        QMetaObject::connectSlotsByName(AEDWindow);
    } // setupUi

    void retranslateUi(QMainWindow *AEDWindow)
    {
        AEDWindow->setWindowTitle(QCoreApplication::translate("AEDWindow", "AEDWindow", nullptr));
        step1_image->setText(QCoreApplication::translate("AEDWindow", "Image", nullptr));
        step2_image->setText(QCoreApplication::translate("AEDWindow", "Image", nullptr));
        step3_image->setText(QCoreApplication::translate("AEDWindow", "Image", nullptr));
        step4_image->setText(QCoreApplication::translate("AEDWindow", "Image", nullptr));
        step5_image->setText(QCoreApplication::translate("AEDWindow", "Image", nullptr));
        step6_image->setText(QCoreApplication::translate("AEDWindow", "Image", nullptr));
        power_button->setText(QCoreApplication::translate("AEDWindow", "Power", nullptr));
        heartRate_label->setText(QCoreApplication::translate("AEDWindow", "Heart Rate Label", nullptr));
        pushButton->setText(QCoreApplication::translate("AEDWindow", "PushButton", nullptr));
        pushButton_2->setText(QCoreApplication::translate("AEDWindow", "PushButton", nullptr));
        pushButton_3->setText(QCoreApplication::translate("AEDWindow", "PushButton", nullptr));
        pushButton_4->setText(QCoreApplication::translate("AEDWindow", "PushButton", nullptr));
        pushButton_5->setText(QCoreApplication::translate("AEDWindow", "PushButton", nullptr));
        pushButton_6->setText(QCoreApplication::translate("AEDWindow", "PushButton", nullptr));
        shock_button->setText(QCoreApplication::translate("AEDWindow", "Shock da bitch", nullptr));
        padsPlacement_image->setText(QCoreApplication::translate("AEDWindow", "Image", nullptr));
        statusLight_image->setText(QCoreApplication::translate("AEDWindow", "Status Light", nullptr));
        label->setText(QCoreApplication::translate("AEDWindow", "Status", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AEDWindow: public Ui_AEDWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AEDWINDOW_H
