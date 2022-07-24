/********************************************************************************
** Form generated from reading UI file 'MyGLWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYGLWIDGET_H
#define UI_MYGLWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyGLWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;

    void setupUi(QWidget *MyGLWidget)
    {
        if (MyGLWidget->objectName().isEmpty())
            MyGLWidget->setObjectName(QString::fromUtf8("MyGLWidget"));
        MyGLWidget->resize(444, 323);
        horizontalLayout = new QHBoxLayout(MyGLWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new QWidget(MyGLWidget);
        widget->setObjectName(QString::fromUtf8("widget"));

        horizontalLayout->addWidget(widget);


        retranslateUi(MyGLWidget);

        QMetaObject::connectSlotsByName(MyGLWidget);
    } // setupUi

    void retranslateUi(QWidget *MyGLWidget)
    {
        MyGLWidget->setWindowTitle(QCoreApplication::translate("MyGLWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyGLWidget: public Ui_MyGLWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYGLWIDGET_H
