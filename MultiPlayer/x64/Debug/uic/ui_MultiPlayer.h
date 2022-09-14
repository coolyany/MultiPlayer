/********************************************************************************
** Form generated from reading UI file 'MultiPlayer.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MULTIPLAYER_H
#define UI_MULTIPLAYER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "MyGraphicsView.h"

QT_BEGIN_NAMESPACE

class Ui_MultiPlayer
{
public:
    QAction *action_local;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    MyGraphicsView *graphicsView;
    QHBoxLayout *horizontalLayout;
    QLabel *label_pre;
    QSlider *horizontalSlider;
    QLabel *label_last;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_play;
    QPushButton *pushButton_stop;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menubar;
    QMenu *menu_media;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MultiPlayer)
    {
        if (MultiPlayer->objectName().isEmpty())
            MultiPlayer->setObjectName(QString::fromUtf8("MultiPlayer"));
        MultiPlayer->resize(619, 386);
        action_local = new QAction(MultiPlayer);
        action_local->setObjectName(QString::fromUtf8("action_local"));
        centralwidget = new QWidget(MultiPlayer);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        graphicsView = new MyGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, 0, 10, 5);
        label_pre = new QLabel(centralwidget);
        label_pre->setObjectName(QString::fromUtf8("label_pre"));

        horizontalLayout->addWidget(label_pre);

        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSlider);

        label_last = new QLabel(centralwidget);
        label_last->setObjectName(QString::fromUtf8("label_last"));

        horizontalLayout->addWidget(label_last);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 5, -1, -1);
        pushButton_play = new QPushButton(centralwidget);
        pushButton_play->setObjectName(QString::fromUtf8("pushButton_play"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/tool/resource/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_play->setIcon(icon);
        pushButton_play->setFlat(true);

        horizontalLayout_2->addWidget(pushButton_play);

        pushButton_stop = new QPushButton(centralwidget);
        pushButton_stop->setObjectName(QString::fromUtf8("pushButton_stop"));

        horizontalLayout_2->addWidget(pushButton_stop);

        horizontalSpacer = new QSpacerItem(444, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        MultiPlayer->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MultiPlayer);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 619, 22));
        menu_media = new QMenu(menubar);
        menu_media->setObjectName(QString::fromUtf8("menu_media"));
        MultiPlayer->setMenuBar(menubar);
        statusbar = new QStatusBar(MultiPlayer);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MultiPlayer->setStatusBar(statusbar);

        menubar->addAction(menu_media->menuAction());
        menu_media->addAction(action_local);

        retranslateUi(MultiPlayer);

        QMetaObject::connectSlotsByName(MultiPlayer);
    } // setupUi

    void retranslateUi(QMainWindow *MultiPlayer)
    {
        MultiPlayer->setWindowTitle(QCoreApplication::translate("MultiPlayer", "MainWindow", nullptr));
        action_local->setText(QCoreApplication::translate("MultiPlayer", "\346\234\254\345\234\260\345\252\222\344\275\223", nullptr));
        label_pre->setText(QCoreApplication::translate("MultiPlayer", "00:00", nullptr));
        label_last->setText(QCoreApplication::translate("MultiPlayer", "00:00", nullptr));
        pushButton_play->setText(QString());
        pushButton_stop->setText(QCoreApplication::translate("MultiPlayer", "\345\201\234\346\255\242", nullptr));
        menu_media->setTitle(QCoreApplication::translate("MultiPlayer", "\345\252\222\344\275\223", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MultiPlayer: public Ui_MultiPlayer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MULTIPLAYER_H
