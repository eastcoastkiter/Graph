#include "graphValue.h"


GraphValue::GraphValue(QColor c,QGraphicsItem * parent): QGraphicsItem ( parent )
{
C=c;
}

void GraphValue::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    (void) option;

    /* Shadow
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(3, 3, 10, 10);
    */

    painter->setBrush(C);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(0, 0, 1, 1);

}

QRectF GraphValue::boundingRect() const
{

    //return QRectF( -10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust);
    return QRectF( -1, -1, 1, 1);
}


