#include "cfwtcp.h"
#include <QTcpSocket>

CFWTcp::CFWTcp(QObject *parent) : QObject(parent)
{
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(ReadMessage()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(DisplayError(QAbstractSocket::SocketError)));

}

CFWTcp::~CFWTcp()
{

}


void CFWTcp::New()
{
    NewConnect();
}


void CFWTcp::ResolveMessage(QString message)
{
    QString deviceType, cmd, value, lt;
    //split message to cmd string
    QStringList cmdList = message.split(",");
    deviceType = cmdList[0];

    if(deviceType != "W")
        return;
    cmd = cmdList[1];

    if(cmd == "MOVE")
    {
        value = cmdList[2];
        lt = cmdList[3];
        //emit signal set filter wheel position
        emit SetWPos(value.toLong());
    }
    else if(cmd == "STATUS")
    {
        value = "";
        lt = cmdList[2];
        //emit signal get filter wheel status
        emit GetWStatus(&cfwStatus.curPos, &cfwStatus.movStatus);
        qDebug()<<"cfwStatus.curPos"<<cfwStatus.curPos;
        qDebug()<<"cfwStatus.movStatus"<<cfwStatus.movStatus;
    }else
        return;

}

void CFWTcp::NewConnect()
{
    //
    blockSize = 0;

    //cancel existed connection
    tcpSocket->abort();
    tcpSocket->connectToHost("190.168.1.115", 6666);

}

void CFWTcp::ReadMessage()
{
    //receive tcp message
    QByteArray in = tcpSocket->readAll();

    message = QString(in);

    qDebug()<<"message: "<<message;

    //handle message: set filterwheel position, get filterwheel position

    ResolveMessage(message);

}

void CFWTcp::DisplayError(QAbstractSocket::SocketError)
{
    qDebug()<<tcpSocket->errorString();
}

