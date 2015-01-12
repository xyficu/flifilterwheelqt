#ifndef CFWTCP_H
#define CFWTCP_H

#include <QObject>
#include "cfwtcpcmd.h"
#include <QAbstractSocket>
#include <QThread>

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


    void ResolveMessage(QString message);


private slots:
    void NewConnect();
    void ReadMessage();
    void DisplayError(QAbstractSocket::SocketError);

signals:
    void SetWPos(long pos);
    void GetWpos(long *pos);
    void GetWStatus(long *status);

public slots:
};



#endif // CFWTCP_H
