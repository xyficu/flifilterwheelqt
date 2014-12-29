#include "cfwthread.h"
#include <QDebug>

CFWThread::CFWThread(QObject *parent) :
    QThread(parent)
{
    stopped = false;
    filterWheel.InitCFW12();

}

void CFWThread::stop()
{
    stopped=true;
}

void CFWThread::run()
{
    qreal i = 0;
    while(!stopped){
        filterWheel.ReConn();
        qDebug()<<QString("in CFWThread: %1").arg(i);
        msleep(1000);
        i++;
    }
    stopped=false;
}

void CFWThread::LogToFile(QString str)
{

}

void CFWThread::GetWPos(long &pos)
{
    filterWheel.GetWheelPos(pos);
}

void CFWThread::SetWPos(long pos)
{
    filterWheel.SetWheelPos(pos);
}

void CFWThread::GetWStatus(long &pos)
{
    pos = filterWheel.GetStatus();
}

void CFWThread::GetLibVer(char **libVer)
{
    *libVer=filterWheel.GetLibVer();
}

void CFWThread::GetWConStatus(bool &conStatus)
{
    conStatus=filterWheel.GetConnStatus();
}


