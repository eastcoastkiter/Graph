#include "graphKey.h"


GraphKey::GraphKey(QGraphicsItem * parent): QGraphicsItem ( parent )
{
   // nRect=scene()->itemsBoundingRect();
}

void GraphKey::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    (void) option;
    nRect=scene()->itemsBoundingRect();
    QRectF iRect=scene()->itemsBoundingRect();
    //QRectF sRect = QPolygonF(scene()->mapToScene( viewport()->geometry())).boundingRect();

    //qDebug() <<"iRect.right()"<<iRect.right();


    painter->setPen(QPen(Qt::black, 0));
    painter->setBrush(Qt::darkGray);
    painter->setFont(QFont("Times", 4));
    //hline
    painter->drawLine(scene()->sceneRect().left(), 0, iRect.right(), 0);
    //vline
    painter->drawLine(0, scene()->sceneRect().bottom(), 0, scene()->sceneRect().top());

    //hruler
    painter->setPen(QPen(Qt::black,0,Qt::DotLine));
    for (int x=100;x<scene()->sceneRect().right();x=x+100)
    {
        painter->drawLine(x, scene()->sceneRect().bottom(), x, scene()->sceneRect().top());
        //painter->drawText(x, 10,QString::number(x/10));
        painter->drawText(QRectF(x, 10,20,20), Qt::AlignCenter, QString::number(x/10));
    }

    //vruler
    for (int y=100;y<(scene()->sceneRect().height()/2);y=y+100)
    {
        painter->drawLine(0, y, scene()->sceneRect().right(),y);
        painter->drawText(10, y,QString::number((y/10)*-1));
        painter->drawLine(0, y*-1, scene()->sceneRect().right(),y*-1);
        painter->drawText(10, y*-1,QString::number((y/10)));
    }

}

QRectF GraphKey::boundingRect() const
{

    return QRectF( -1, -1, nRect.width(), nRect.height()/2);
}


