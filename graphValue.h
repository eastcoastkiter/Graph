#ifndef GRAPHVALUE_H
#define GRAPHVALUE_H

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

class GraphValue : public QGraphicsItem
{
public:
    GraphValue(QColor c=QColor(Qt::green),QGraphicsItem *parent=0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QColor C;
public slots:
private:
protected:
};

#endif // GraphValue_H
