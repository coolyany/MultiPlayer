/********************************************************************************
** Form generated from reading UI file 'CameraDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERADIALOG_H
#define UI_CAMERADIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CameraDialog
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QComboBox *comboBox;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *CameraDialog)
    {
        if (CameraDialog->objectName().isEmpty())
            CameraDialog->setObjectName(QString::fromUtf8("CameraDialog"));
        CameraDialog->resize(476, 177);
        verticalLayout = new QVBoxLayout(CameraDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 42, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        comboBox = new QComboBox(CameraDialog);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout->addWidget(comboBox);

        verticalSpacer = new QSpacerItem(20, 41, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(CameraDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(CameraDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        verticalLayout->addLayout(hboxLayout);


        retranslateUi(CameraDialog);
        QObject::connect(okButton, SIGNAL(clicked()), CameraDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), CameraDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(CameraDialog);
    } // setupUi

    void retranslateUi(QDialog *CameraDialog)
    {
        CameraDialog->setWindowTitle(QCoreApplication::translate("CameraDialog", "\346\211\223\345\274\200\346\221\204\345\203\217\345\244\264\350\256\276\345\244\207", nullptr));
        okButton->setText(QCoreApplication::translate("CameraDialog", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("CameraDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CameraDialog: public Ui_CameraDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERADIALOG_H
