#ifndef CFWTHREAD_H
#define CFWTHREAD_H

#include <QObject>
#include <QThread>
#include "cfw12.h"

class CFWThread : public QThread
{
    Q_OBJECT
public:
    explicit CFWThread(QObject *parent = 0);

    void stop();
protected:
    void run();

private:
    volatile bool stopped;
    CFW12 filterWheel;

signals:

public slots:
    //
    void GetWPos(long &pos);
    void SetWPos(long pos);
    void GetWStatus(long pos);
    void GetLibVer(char** libVer);
    void GetWConStatus(bool &conStatus);

};

#endif // CFWTHREAD_H
