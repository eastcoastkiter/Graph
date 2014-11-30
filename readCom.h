#ifndef READCOM_H
#define READCOM_H

#include <QObject>
#include <QDebug>
#include <QByteArray>
#include <QRegExp>
#include <QString>
#include <QCoreApplication>
#include <QTimer>


#include "math.h"

class ReadCom: public QObject
{
    Q_OBJECT

public:
     ReadCom(QString portName="COM1", int baudRate=9600){ stop=false; n=portName; b=baudRate; i=0.0;}
     ~ReadCom(){ stop=true; } // port->close(); }
public:

    bool stop;
    QString n;
    int b;
    bool isOpen;
    double i;
public slots:
    void startCom();
    void close(){};
    void emitData();

signals:
    void resultReady(const QString &result);
};
#endif


