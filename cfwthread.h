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

signals:

public slots:

};

#endif // CFWTHREAD_H
