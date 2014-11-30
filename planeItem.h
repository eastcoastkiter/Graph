#ifndef PLANEITEM_H
#define PLANEITEM_H

#include <QDebug>
#include <QGLWidget>
#include <qopengl.h>

#include <QMouseEvent>

#include "math.h"
class PlaneItem : public QGLWidget
{
    Q_OBJECT        // must include this if you use Qt signals/slots

public:
    PlaneItem(QWidget *parent);
    ~PlaneItem();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

private:
        void draw();
        int xRot;
        int yRot;
        int zRot;

        QPoint lastPos;
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void vertex(double, double);
    void drawCube(float, float, float, float, float, float, int, int, int, int);
signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

};

#endif // PLANEITEM_H
