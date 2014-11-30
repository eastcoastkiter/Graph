#include "graphView.h"


GraphView::GraphView(QGraphicsScene * scene, QWidget * parent) : QGraphicsView (scene, parent)
{
    yScale=0;
    setAttribute(Qt::WA_AcceptTouchEvents);
    setDragMode(ScrollHandDrag);

       setMouseTracking(true);
       setRenderHint(QPainter::Antialiasing, true);
       setRenderHint(QPainter::TextAntialiasing, true);
       setRenderHint(QPainter::SmoothPixmapTransform, true);
       //setAlignment((Qt::AlignRight | Qt::AlignTop));

       createGKey();


}

void GraphView::createGKey()
{
     gKey = new GraphKey(0);
     scene()->addItem(gKey);
     gKey->setZValue(2);
}

void GraphView::autoScroll()
{
    setResizeAnchor(QGraphicsView::AnchorViewCenter);
    setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    QRectF iRect=scene()->itemsBoundingRect();
    QRectF sRect = QPolygonF(mapToScene( viewport()->geometry())).boundingRect();

   // qDebug() << "Rect" << iRect.right() << sRect.right();

    //centerOn(sRect.width()-(iRect.width()/2),0);
    ensureVisible(iRect.right(),0,sRect.width(),sRect.height(),50,50);
    gKey->update();
    update();
   /*
    *  if (iRect.right()>sRect.right())
    {
//        translate((iRect.right()-sRect.right()),0);

    }
*/
}

void GraphView::autoScale()
{
    setResizeAnchor(QGraphicsView::AnchorViewCenter);
    QRectF iRect=scene()->itemsBoundingRect();
    QRectF sRect = QPolygonF(mapToScene( viewport()->geometry())).boundingRect();

    qreal wfactor=sRect.width()/iRect.width();
    wfactor=wfactor*0.85;
    qreal hfactor=sRect.height()/iRect.height();
    hfactor=hfactor*0.85;


    //qDebug() << "wfactor" << wfactor << hfactor;


       if (wfactor < hfactor)
        {
            scale(wfactor,wfactor);
        }
        else
        {
            scale (hfactor,hfactor);
        }


 /*   qDebug() << "wfactor" << wfactor << iRect.width()<< width();
    if (iRect.width()<(width()))
    scale (wfactor,1);
*/
}

bool GraphView::viewportEvent(QEvent *event)
{
    switch (event->type()) {
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd:
    {
        QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
        QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints();
        if (touchPoints.count() == 2) {
            // determine scale factor
            const QTouchEvent::TouchPoint &touchPoint0 = touchPoints.first();
            const QTouchEvent::TouchPoint &touchPoint1 = touchPoints.last();
            qreal currentScaleFactor =
                    QLineF(touchPoint0.pos(), touchPoint1.pos()).length()
                    / QLineF(touchPoint0.startPos(), touchPoint1.startPos()).length();
            if (touchEvent->touchPointStates() & Qt::TouchPointReleased) {
                // if one of the fingers is released, remember the current scale
                // factor so that adding another finger later will continue zooming
                // by adding new scale factor to the existing remembered value.
                totalScaleFactor *= currentScaleFactor;
                currentScaleFactor = 1;
            }
            setTransform(QTransform().scale(totalScaleFactor * currentScaleFactor,
                                            totalScaleFactor * currentScaleFactor));
        }
        return true;
    }
    default:
        break;
    }
    return QGraphicsView::viewportEvent(event);
}


/*
void GraphView::wheelEvent(QWheelEvent* event)
{
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    //setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // Scale the view / do the zoom
    double scaleFactor = 1.15;
    if(event->delta() > 0) {
        // Zoom in
        scale(scaleFactor, scaleFactor);
    } else {
        // Zooming out
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }

    // Don't call superclass handler here
    // as wheel is normally used for moving scrollbars
}

//void GraphView::mouseDoubleClickEvent(QMouseEvent * mouseEvent)
void GraphView::mouseMoveEvent(QMouseEvent * mouseEvent)
{

    qreal PI=3.1415926535;

    int sx=mapToScene(mouseEvent->pos()).x();
    int sy=mapToScene(mouseEvent->pos()).y();
    //qDebug() << "doubleclicked" << sx << sy << scene()->items(QPointF(sx,sy)).count();
    qreal clicked_X=sx-140;
    qreal clicked_Y=sy-120;

   //qDebug() << "click_X" << clicked_X << clicked_Y;

/*
    for (int i=0;i<scene()->items(QPointF(sx,sy)).count();i++)
    {
        if ((scene()->items(QPointF(sx,sy)).at(i))->type() == 11111)
        {
            StateCyclePieItem * item = dynamic_cast<StateCyclePieItem*>(scene()->items(QPointF(sx,sy)).at(i));
            int From=item->getDiffFrom();
            int Until=item->getDiffUntil();
            int Length=item->getLength();

            qreal degreeStep = 360.0 / Length;
            qreal startAngle = Until * degreeStep;
            qreal stopAngle  = From * degreeStep;

            // could happen in search //we livestatus for start
            if (stopAngle>360)
                stopAngle=360.0;

            qreal par = clicked_Y/clicked_X;
            //qreal angle = (atan(par)*PI/180);
             qreal angle = atan2 (clicked_Y,clicked_X) * 180 / PI;
             angle=angle+90;
             if (angle<0)
                 angle=360.0+angle;

            //qDebug() << Length << From << Until << startAngle << stopAngle;
            //qDebug() << "par" << par << "angle" << angle;

            if ( (startAngle<angle) && (stopAngle>angle) )
            {
                QString LogOutput=item->getLogOutput();
                 //*tip = new QToolTip(this);
                int gx = mapToGlobal(mouseEvent->pos()).x();
                int gy = mapToGlobal(mouseEvent->pos()).y();
                QToolTip::showText(QPoint(gx,gy), LogOutput, this);

                //qDebug() << LogOutput;
                break;

            }
        }
    }
    //mouseEvent->accept();

    */
//}

