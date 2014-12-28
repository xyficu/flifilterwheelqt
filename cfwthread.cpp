#include "cfwthread.h"
#include <QDebug>

CFWThread::CFWThread(QObject *parent) :
    QThread(parent)
{
    stopped = false;
}

void CFWThread::stop()
{
    stopped=true;
}

void CFWThread::run()
{
    qreal i = 0;
    while(!stopped){
        qDebug()<<QString("in CFWThread: %1").arg(i);
        msleep(1000);
        i++;
    }
    stopped=false;
}


