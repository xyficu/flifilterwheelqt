#include "cfw12.h"

CFW12::CFW12(QObject *parent) :
  QObject(parent)
{
    dev_filterWheel = FLI_INVALID_DEVICE;
    status = 0;

    timer = new QTimer(this);
    InitCFW12();

    connect(timer, SIGNAL(timeout()), this, SLOT(CheckConn()));
    timer->start(100);
}

CFW12::~CFW12()
{
    FLIClose(dev_filterWheel);
    m_connect = false;
}

bool CFW12::GetConnStatus()
{
    return m_connect;
}

char *CFW12::GetLibVer()
{
    return libver;
}


//set the filter wheel position
void CFW12::SetWheelPos(long filter)
{
    if(false == m_connect)
        return;
    else
    {
        FLISetFilterPos(dev_filterWheel, filter);
        return;
    }
}

//get the filter wheel position
void CFW12::GetWheelPos(long &filter)
{
    if(false == m_connect)
        return;

    if (0 != FLIGetFilterPos(dev_filterWheel, &filter))
    {
        //Qmessagebox error;
        return;
    }

}

long CFW12::GetStatus()
{
    return status;
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

void CFW12::CheckConn()
{
//    //获取FLI设备列表
//    if (0 != FLICreateList(FLIDOMAIN_USB | FLIDEVICE_FILTERWHEEL))
//    {
//        m_connect = false;
//    }
//    else if (0 != FLIListFirst(&dev_filterWheel, file, MAX_PATH, name, MAX_PATH))
//    {
//        m_connect = false;
//    }

//    if(false == m_connect)
//    {
//        FLIClose(dev_filterWheel);
//        InitCFW12();
//    }
}

