#include "readCom.h"
using namespace std;

void ReadCom::startCom()
{
    //qDebug() << n << b;
    port = new QSerialPort(n);
    //port->setPortName(n);
    port->open(QIODevice::ReadOnly);
        qDebug() << "open";
        port->setBaudRate(b);
        port->setDataBits(QSerialPort::Data8);
        port->setParity(QSerialPort::NoParity);
        port->setStopBits(QSerialPort::OneStop);

        QByteArray responseData;
        forever
        {
            isOpen=true;
            if (port->waitForReadyRead(10))
            {
                responseData += port->readAll();
                while (port->waitForReadyRead(0))
                {
                    responseData += port->readAll();
                           }
               // qDebug() << "responseData" << responseData.replace("|",";");
                    if (responseData.contains("|"))
                    {
                        int space = responseData.lastIndexOf("|");
                        //qDebug() << "contains" << space <<responseData.left(space);
                        emit resultReady(responseData.left(space));
                        responseData=responseData.right(responseData.length()-(space+1));
                    }
                    if (stop)
                    {
                        break;
                    }
                }
         }


}
