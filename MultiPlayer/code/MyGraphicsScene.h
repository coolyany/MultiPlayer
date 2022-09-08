#pragma once
#include <qgraphicsscene.h>

class MyGraphicsScene : public QGraphicsScene
{
	Q_OBJECT
public:
	MyGraphicsScene(QObject *parent = nullptr);
	~MyGraphicsScene();

private:


};