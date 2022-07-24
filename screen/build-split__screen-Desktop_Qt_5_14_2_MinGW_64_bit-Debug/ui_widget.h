/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_One;
    QPushButton *pushButton_Four;
    QPushButton *pushButton_Six;
    QPushButton *pushButton_Nine;
    QPushButton *pushButton_Sixteen;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 600);
        widget = new QWidget(Widget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 560, 417, 45));
        widget->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:0.0738636 rgba(235, 148, 61, 255), stop:0.982955 rgba(255, 178, 102, 255), stop:1 rgba(0, 0, 0, 0));"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_One = new QPushButton(widget);
        pushButton_One->setObjectName(QString::fromUtf8("pushButton_One"));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(14);
        pushButton_One->setFont(font);
        pushButton_One->setStyleSheet(QString::fromUtf8("background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(255, 255, 0, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));"));

        horizontalLayout->addWidget(pushButton_One);

        pushButton_Four = new QPushButton(widget);
        pushButton_Four->setObjectName(QString::fromUtf8("pushButton_Four"));
        pushButton_Four->setFont(font);
        pushButton_Four->setStyleSheet(QString::fromUtf8("background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(255, 255, 0, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));"));

        horizontalLayout->addWidget(pushButton_Four);

        pushButton_Six = new QPushButton(widget);
        pushButton_Six->setObjectName(QString::fromUtf8("pushButton_Six"));
        pushButton_Six->setFont(font);
        pushButton_Six->setStyleSheet(QString::fromUtf8("background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(255, 255, 0, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));"));

        horizontalLayout->addWidget(pushButton_Six);

        pushButton_Nine = new QPushButton(widget);
        pushButton_Nine->setObjectName(QString::fromUtf8("pushButton_Nine"));
        pushButton_Nine->setFont(font);
        pushButton_Nine->setStyleSheet(QString::fromUtf8("background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(255, 255, 0, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));"));

        horizontalLayout->addWidget(pushButton_Nine);

        pushButton_Sixteen = new QPushButton(widget);
        pushButton_Sixteen->setObjectName(QString::fromUtf8("pushButton_Sixteen"));
        pushButton_Sixteen->setFont(font);
        pushButton_Sixteen->setStyleSheet(QString::fromUtf8("background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(255, 255, 0, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));"));

        horizontalLayout->addWidget(pushButton_Sixteen);


        retranslateUi(Widget);
        QObject::connect(pushButton_One, SIGNAL(clicked()), Widget, SLOT(show_1()));
        QObject::connect(pushButton_Six, SIGNAL(clicked()), Widget, SLOT(show_6()));
        QObject::connect(pushButton_Four, SIGNAL(clicked()), Widget, SLOT(show_4()));
        QObject::connect(pushButton_Nine, SIGNAL(clicked()), Widget, SLOT(show_9()));
        QObject::connect(pushButton_Sixteen, SIGNAL(clicked()), Widget, SLOT(show_16()));

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        pushButton_One->setText(QCoreApplication::translate("Widget", "One", nullptr));
        pushButton_Four->setText(QCoreApplication::translate("Widget", "Four", nullptr));
        pushButton_Six->setText(QCoreApplication::translate("Widget", "Six", nullptr));
        pushButton_Nine->setText(QCoreApplication::translate("Widget", "Nine", nullptr));
        pushButton_Sixteen->setText(QCoreApplication::translate("Widget", "Sixteen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
