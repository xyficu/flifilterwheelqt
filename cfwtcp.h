#ifndef CFWTCP_H
#define CFWTCP_H

#include <QObject>
#include "cfwtcpcmd.h"
#include <QAbstractSocket>
#include "cfwtcpparams.h"
#include <QTimer>
#include <QDateTime>

class QTcpSocket;

//filter wheel tcp thread
//connect to the telescope controller, receive command to drive filter wheel, reply status
class CFWTcp : public QObject
{
    Q_OBJECT
public:
    explicit CFWTcp(QObject *parent = 0);
    ~CFWTcp();
    void New();

protected:

private:
    QTcpSocket *tcpSocket;
    QString message;
    quint16 blockSize;
    bool tcpCon;
    QTimer m_tmrHouseKp;
    QDateTime m_dateTime;
    void ResolveMessage(QString message);

    WheelStatus cfwStatus;

    void ReConnToHost();
    void RegisterDevice();
    void DeregisterDevice();


private slots:
    void NewConnect();
    void StopConnect();
    void ReadMessage();
    void DisplayError(QAbstractSocket::SocketError);
    void OnConnected();
    void OnDisconnected();
    void OnAboutToClose();
    void HouseKeeping();

signals:
    void SetWPos(long pos);
    void GetWpos(long *pos);
    void GetWStatus(long *curPos, long *movStatus);

public slots:
};



#endif // CFWTCP_H
