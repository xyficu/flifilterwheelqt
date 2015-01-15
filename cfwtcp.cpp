#include "cfwtcp.h"
#include <QTcpSocket>
#include <QThread>
#include <QHostAddress>

CFWTcp::CFWTcp(QObject *parent) : QObject(parent)
{
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(ReadMessage()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(DisplayError(QAbstractSocket::SocketError)));
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(OnConnected()));
    connect(tcpSocket, SIGNAL(aboutToClose()), this, SLOT(OnAboutToClose()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(OnDisconnected()));
}

CFWTcp::~CFWTcp()
{
    tcpSocket->close();
}


void CFWTcp::ResolveMessage(QString message)
{
    try
    {
        QString deviceType, cmd, value, lt;
        //split message to cmd string
        QStringList cmdList = message.split(",");
        deviceType = cmdList[0];

        if(cmdList.count()<3)
            return;
        if(deviceType != "W")
            return;
        cmd = cmdList[1];

        if(cmd == "MOVE")
        {
            value = cmdList[2];
            lt = cmdList[3];
            //emit signal set filter wheel position
            emit SetWPos(value.toLong());
            //send reply message
            QString reply = "R"+
                    deviceType+","+
                    cmd+","+
                    "0"+","+
                    lt;
            tcpSocket->write(reply.toLatin1());
            tcpSocket->waitForBytesWritten();
            qDebug()<<"send:"<<reply;


        }
        else if(cmd == "STATUS")
        {
            value = "";
            lt = cmdList[2];
            //emit signal get filter wheel status
            emit GetWStatus(&cfwStatus.curPos, &cfwStatus.movStatus);
            //send replay message
            QString reply = "R"+
                    deviceType+","+
                    cmd+","+
                    QString::number(cfwStatus.curPos)+","+
                    QString::number(cfwStatus.movStatus)+","+
                    lt;

            tcpSocket->write(reply.toLatin1());
            tcpSocket->waitForBytesWritten();
            qDebug()<<"send:"<<reply;
            qDebug()<<"cfwStatus.curPos"<<cfwStatus.curPos;
            qDebug()<<"cfwStatus.movStatus"<<cfwStatus.movStatus;
        }else
            return;
    }
    catch(QString exception)
    {
        qDebug()<<"Resolve message error: "<<exception;
    }
}

void CFWTcp::ReConnToHost()
{
    //if socket is down try to reconnect to the host
    tcpCon = false;
    while(!tcpCon)
    {
        qDebug()<<"try to connect to host...";
        tcpSocket->connectToHost("190.168.1.115", 30001);
        tcpSocket->waitForConnected();
        QThread::sleep(5);
    }
}

void CFWTcp::NewConnect()
{
    //
    blockSize = 0;

    //cancel existed connection
    tcpSocket->abort();
//    tcpSocket->connectToHost("190.168.1.115", 30001);
//    tcpSocket->waitForConnected();
    ReConnToHost();

}

void CFWTcp::StopConnect()
{
    tcpCon = true;
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
    qDebug()<<"socket error:"<<tcpSocket->errorString();
}

void CFWTcp::OnConnected()
{
    tcpCon = true;
    qDebug()<<"connect to host"<<tcpSocket->peerAddress().toString()<<":"<<tcpSocket->peerPort()<<"successfully!";
    RegisterDevice();
}

void CFWTcp::OnDisconnected()
{
    ReConnToHost();
}

void CFWTcp::OnAboutToClose()
{
    DeregisterDevice();
}


void CFWTcp::RegisterDevice()
{
    //send register message
    QByteArray deviceRegMsg = QByteArray("WHEEL");
    tcpSocket->write(deviceRegMsg);
    tcpSocket->waitForBytesWritten();

}

void CFWTcp::DeregisterDevice()
{
    //send deregister message
    QByteArray deviceRegMsg = QByteArray("RWHEEL");
    tcpSocket->write(deviceRegMsg);
    tcpSocket->waitForBytesWritten();

}

