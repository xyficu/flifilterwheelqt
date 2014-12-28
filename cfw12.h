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
    bool GetConnStatus();
    char* GetLibVer();

private slots:
    void ReConn();

public:
    void SetWheelPos(long filter);
    void GetWheelPos(long &filter);
    long GetStatus();
    void InitCFW12();

private:
    bool m_connect;
    char libver[LIBVERSIZE];
    flidev_t dev_filterWheel;
    char file[MAX_PATH], name[MAX_PATH];
    long status;
    QTimer *timer;



protected:


};

#endif // CFW12_H
