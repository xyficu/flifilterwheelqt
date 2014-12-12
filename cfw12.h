#ifndef CFW12_H
#define CFW12_H

#include "libfli.h"
#include <stdio.h>
#define LIBVERSIZE 500
#define MAX_PATH 260
#define FLIFILTERWHEELCTRL_VER "0.01"

class CFW12
{
public:
    CFW12();
    ~CFW12();
    bool GetConnStatus();
    char* GetLibVer();

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

protected:


};

#endif // CFW12_H
