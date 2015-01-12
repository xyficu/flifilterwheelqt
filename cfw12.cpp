#include "cfw12.h"
#include "QDebug"

CFW12::CFW12(QObject *parent) :
  QObject(parent)
{
    dev_filterWheel = FLI_INVALID_DEVICE;
    m_movStatus = -1;

    timer = new QTimer(this);
    InitCFW12();

    connect(timer, SIGNAL(timeout()), this, SLOT(ReConn()));
    timer->start(1000);

}

CFW12::~CFW12()
{
    FLIClose(dev_filterWheel);
    m_connect = false;

}

//set the filter wheel position
void CFW12::SetWheelPos(long pos)
{
    if(false == m_connect)
        return;
    else
    {
        SetMoveStatus(1);
        FLISetFilterPos(dev_filterWheel, pos);
        SetMoveStatus(0);
        return;
    }
}

//get the filter wheel position
void CFW12::GetWheelPos(long *pos)
{

    if(false == m_connect)
    {
//        *pos = filter;
        return;
    }
    if (0 != FLIGetFilterPos(dev_filterWheel, pos))
    {
//        *pos = filter;
        return;
    }

}

void CFW12::GetWheelConnStatus(bool *value)
{
    *value = m_connect;
}

void CFW12::GetWheelLibVer(char **value)
{
    *value = libver;
}

void CFW12::GetWheelMoveStatus(long *value)
{
    *value = m_movStatus;
}

void CFW12::InitCFW12()
{
    //test if lib loads correctly

    if(FLIGetLibVersion(libver, LIBVERSIZE) != 0)
    {
        m_connect = false;
        return;
    }

    //获取FLI设备列表
    if (0 != FLICreateList(FLIDOMAIN_USB | FLIDEVICE_FILTERWHEEL))
    {
        m_connect = false;
        return;
    }
    else if (0 != FLIListFirst(&dev_filterWheel, file, MAX_PATH, name, MAX_PATH))
    {
        m_connect = false;
        return;
    }

    //打开FLI filter wheel
    if (0 == FLIOpen(&dev_filterWheel, file, (FLIDOMAIN_USB | FLIDEVICE_FILTERWHEEL)))
    {

        m_connect = true;
        return;
    }
    else
    {

        m_connect = false;
        return;
    }
}

void CFW12::StopTimer()
{
    timer->stop();
}

void CFW12::SetMoveStatus(long value)
{
    m_movStatus=value;
}


void CFW12::ReConn()
{
    //获取FLI设备列表
    if (0 != FLICreateList(FLIDOMAIN_USB | FLIDEVICE_FILTERWHEEL))
    {
        m_connect = false;
    }
    else if (0 != FLIListFirst(&dev_filterWheel, file, MAX_PATH, name, MAX_PATH))
    {
        m_connect = false;
    }

    if(false == m_connect)
    {
        FLIClose(dev_filterWheel);
        InitCFW12();
        qDebug()<<QString("ReConn...");

    }

}

