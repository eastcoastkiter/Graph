#ifndef GRAPHKEY_H
#define GRAPHKEY_H

#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QColor>
#include <QDebug>
#include <QTreeWidgetItem>
#include <QMouseEvent>
#include <QFont>

#include "math.h"

class GraphKey : public QGraphicsItem
{
public:
    GraphKey(QGraphicsItem *parent=0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QRectF nRect;
public slots:
private:
protected:
};

#endif // GRAPHKEY_H
