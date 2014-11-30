#include "readCom.h"
using namespace std;

void ReadCom::startCom()
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(emitData()));
    timer->start(1000);
}

void ReadCom::emitData()
{
    i=i+0.3141;
    if (i>= (2*3.141))
    {
        i=0.0;
    }
    double x=sin(i);
    double y=cos(i);

    QString res="x:";
            res+=QString::number(x);
            res+="\ny:";
            res+=QString::number(y);
            res+="\nz:2";
    emit resultReady(res);
}
