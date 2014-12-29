#include "cfwthread.h"
#include <QDebug>
#include <QTime>

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
//    qreal i = 0;
//    while(!stopped){
//        filterWheel.ReConn();
//        qDebug()<<QString("in CFWThread: %1").arg(i);
//        msleep(1000);
//        i++;
//    }
    stopped=false;
}

void CFWThread::LogToFile(QString str)
{
    //
}

void CFWThread::GetWPos(long &pos)
{
    filterWheel.GetWheelPos(pos);
}

void CFWThread::SetWPos(long pos)
{
    if(true==filterWheel.GetConnStatus()){
        //output the position
        long startPos;

        filterWheel.GetWheelPos(startPos);
        qDebug()<<QString("%1 -> %2 Moving...").arg(startPos).arg(pos);

        //cal the rotate time
        QTime time;
        time.start();
        filterWheel.SetWheelPos(pos);
        qDebug()<<time.elapsed()/1000.0<<"s";
    }
}

void CFWThread::GetWStatus(long &status)
{
    status = filterWheel.GetStatus();
}

void CFWThread::GetLibVer(char **libVer)
{
    *libVer=filterWheel.GetLibVer();
}

void CFWThread::GetWConStatus(bool &conStatus)
{
    conStatus=filterWheel.GetConnStatus();
}


