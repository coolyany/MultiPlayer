#pragma once
#include <QThread>
#include "Data.h"

class SDLVideoThead : public QThread
{
	Q_OBJECT
public:
	SDLVideoThead(const Data &data, QObject *parent = NULL);

protected:
	void run();
private:
	Data m_data;
};