#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H



#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QToolTip>
#include <QEvent>
#include <QTouchEvent>

#include "graphKey.h"

#include "math.h"

class GraphView : public QGraphicsView
{
    Q_OBJECT

public:
    GraphView(QGraphicsScene * scene, QWidget * parent = 0);
    ~GraphView(){}
    int yScale;
    GraphKey *gKey;
private:
    qreal totalScaleFactor;
public slots:
    void autoScale();
    void autoScroll();
    void setYScale(int y){ yScale=y; }
    void createGKey();
protected:
//    void wheelEvent(QWheelEvent*);
//    void mouseMoveEvent(QMouseEvent *);
    bool viewportEvent(QEvent *);
};


#endif // GRAPHVIEW_H
