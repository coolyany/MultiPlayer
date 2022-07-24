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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MultiPlayerClass
{
public:
    QAction *action_file;
    QAction *action_stream;
    QAction *action_camera;
    QAction *action_T;
    QAction *action_T_4;
    QAction *action_T_9;
    QAction *action_A;
    QAction *action_T_2;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QMenuBar *menuBar;
    QMenu *menu_media;
    QMenu *menu_view;
    QMenu *menu_help;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MultiPlayerClass)
    {
        if (MultiPlayerClass->objectName().isEmpty())
            MultiPlayerClass->setObjectName(QString::fromUtf8("MultiPlayerClass"));
        MultiPlayerClass->resize(714, 496);
        action_file = new QAction(MultiPlayerClass);
        action_file->setObjectName(QString::fromUtf8("action_file"));
        action_stream = new QAction(MultiPlayerClass);
        action_stream->setObjectName(QString::fromUtf8("action_stream"));
        action_camera = new QAction(MultiPlayerClass);
        action_camera->setObjectName(QString::fromUtf8("action_camera"));
        action_T = new QAction(MultiPlayerClass);
        action_T->setObjectName(QString::fromUtf8("action_T"));
        action_T_4 = new QAction(MultiPlayerClass);
        action_T_4->setObjectName(QString::fromUtf8("action_T_4"));
        action_T_9 = new QAction(MultiPlayerClass);
        action_T_9->setObjectName(QString::fromUtf8("action_T_9"));
        action_A = new QAction(MultiPlayerClass);
        action_A->setObjectName(QString::fromUtf8("action_A"));
        action_T_2 = new QAction(MultiPlayerClass);
        action_T_2->setObjectName(QString::fromUtf8("action_T_2"));
        centralWidget = new QWidget(MultiPlayerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(widget);

        MultiPlayerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MultiPlayerClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 714, 22));
        menu_media = new QMenu(menuBar);
        menu_media->setObjectName(QString::fromUtf8("menu_media"));
        menu_view = new QMenu(menuBar);
        menu_view->setObjectName(QString::fromUtf8("menu_view"));
        menu_help = new QMenu(menuBar);
        menu_help->setObjectName(QString::fromUtf8("menu_help"));
        MultiPlayerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MultiPlayerClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MultiPlayerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MultiPlayerClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MultiPlayerClass->setStatusBar(statusBar);

        menuBar->addAction(menu_media->menuAction());
        menuBar->addAction(menu_view->menuAction());
        menuBar->addAction(menu_help->menuAction());
        menu_media->addAction(action_file);
        menu_media->addAction(action_stream);
        menu_media->addAction(action_camera);
        menu_view->addAction(action_T);
        menu_view->addAction(action_T_2);
        menu_view->addAction(action_T_4);
        menu_view->addAction(action_T_9);
        menu_help->addAction(action_A);
        mainToolBar->addAction(action_file);
        mainToolBar->addAction(action_stream);
        mainToolBar->addAction(action_camera);

        retranslateUi(MultiPlayerClass);

        QMetaObject::connectSlotsByName(MultiPlayerClass);
    } // setupUi

    void retranslateUi(QMainWindow *MultiPlayerClass)
    {
        MultiPlayerClass->setWindowTitle(QCoreApplication::translate("MultiPlayerClass", "MultiPlayer", nullptr));
        action_file->setText(QCoreApplication::translate("MultiPlayerClass", "\346\211\223\345\274\200\346\226\207\344\273\266(&N)", nullptr));
        action_stream->setText(QCoreApplication::translate("MultiPlayerClass", "\346\211\223\345\274\200\344\270\262\346\265\201(&O)", nullptr));
        action_camera->setText(QCoreApplication::translate("MultiPlayerClass", "\346\211\223\345\274\200\346\221\204\345\203\217\345\244\264(&S)", nullptr));
        action_T->setText(QCoreApplication::translate("MultiPlayerClass", "\345\205\250\351\235\242\350\247\206\345\233\276(&T)", nullptr));
        action_T_4->setText(QCoreApplication::translate("MultiPlayerClass", "\345\233\233\345\210\206\345\261\217\350\247\206\345\233\276(&T)", nullptr));
        action_T_9->setText(QCoreApplication::translate("MultiPlayerClass", "\344\271\235\345\210\206\345\261\217\350\247\206\345\233\276(&T)", nullptr));
        action_A->setText(QCoreApplication::translate("MultiPlayerClass", "\345\205\263\344\272\216(&A)", nullptr));
        action_T_2->setText(QCoreApplication::translate("MultiPlayerClass", "\344\272\214\345\210\206\345\261\217\350\247\206\345\233\276", nullptr));
        menu_media->setTitle(QCoreApplication::translate("MultiPlayerClass", "\345\252\222\344\275\223(&M)", nullptr));
        menu_view->setTitle(QCoreApplication::translate("MultiPlayerClass", "\350\247\206\345\233\276(&V)", nullptr));
        menu_help->setTitle(QCoreApplication::translate("MultiPlayerClass", "\345\270\256\345\212\251(&H)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MultiPlayerClass: public Ui_MultiPlayerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MULTIPLAYER_H
