#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MultiPlayer.h"

class MultiPlayer : public QMainWindow
{
    Q_OBJECT

public:
    MultiPlayer(QWidget *parent = Q_NULLPTR);
	~MultiPlayer();

	void initMenu();

private:
    Ui::MultiPlayerClass ui;
};
