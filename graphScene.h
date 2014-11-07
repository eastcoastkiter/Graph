#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QWheelEvent>
#include <QGraphicsView>

class GraphScene: public QGraphicsScene
{
    Q_OBJECT

public:
    GraphScene(QObject * parent = 0);
    ~GraphScene(){}
};

#endif // GRAPHSCENE_H
