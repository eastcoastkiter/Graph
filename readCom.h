#ifndef READCOM_H
#define READCOM_H

#include <QObject>
#include <QSerialPort>
#include <QDebug>
#include <QByteArray>
#include <QRegExp>
#include <QString>
#include <QCoreApplication>

#include "windows.h"

class ReadCom: public QObject
{
    Q_OBJECT

public:
     ReadCom(QString portName="COM1", int baudRate=9600){ stop=false; n=portName; b=baudRate; }
     ~ReadCom(){ stop=true; } // port->close(); }
public:
    QSerialPort* port;
    bool stop;
    QString n;
    int b;
    bool isOpen;

public slots:
    void startCom();
    void close()
    {
        stop=true;
            #ifdef Q_OS_WIN
            Sleep(50);
            #endif
        if (isOpen)
        {
            port->clear();
            port->close();
        }
        isOpen=false;
    }

signals:
    void resultReady(const QString &result);
};
#endif


