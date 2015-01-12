#ifndef CFW12_H
#define CFW12_H

#include "libfli.h"
#include <stdio.h>
#include <QTimer>
#define LIBVERSIZE 100
#define MAX_PATH 260
#define FLIFILTERWHEELCTRL_VER "0.01"

class CFW12: public QObject
{
    Q_OBJECT
public:
    explicit CFW12(QObject *parent = 0);
    ~CFW12();

private slots:
    void ReConn();
    void SetMoveStatus(long value);

    void SetWheelPos(long pos);
    void GetWheelPos(long *pos);
    void GetWheelMoveStatus(long *value);
    void GetWheelConnStatus(bool *value);
    void GetWheelLibVer(char **value);
    void InitCFW12();
    void StopTimer();


private:
    bool m_connect;
    char libver[LIBVERSIZE];
    flidev_t dev_filterWheel;
    char file[MAX_PATH], name[MAX_PATH];
    long m_movStatus;
    QTimer *timer;

protected:


};

#endif // CFW12_H
