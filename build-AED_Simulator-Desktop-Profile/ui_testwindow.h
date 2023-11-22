/********************************************************************************
** Form generated from reading UI file 'testwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTWINDOW_H
#define UI_TESTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestWindow
{
public:
    QFrame *frame;
    QPushButton *audioTest_button;

    void setupUi(QWidget *TestWindow)
    {
        if (TestWindow->objectName().isEmpty())
            TestWindow->setObjectName(QString::fromUtf8("TestWindow"));
        TestWindow->resize(1031, 435);
        frame = new QFrame(TestWindow);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 1011, 411));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        audioTest_button = new QPushButton(frame);
        audioTest_button->setObjectName(QString::fromUtf8("audioTest_button"));
        audioTest_button->setGeometry(QRect(30, 20, 121, 31));

        retranslateUi(TestWindow);

        QMetaObject::connectSlotsByName(TestWindow);
    } // setupUi

    void retranslateUi(QWidget *TestWindow)
    {
        TestWindow->setWindowTitle(QCoreApplication::translate("TestWindow", "Form", nullptr));
        audioTest_button->setText(QCoreApplication::translate("TestWindow", "Play Audio Test", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TestWindow: public Ui_TestWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTWINDOW_H
