#ifndef CFWTCP_H
#define CFWTCP_H

#include <QObject>

class CFWTcp : public QObject
{
    Q_OBJECT
public:
    explicit CFWTcp(QObject *parent = 0);
    ~CFWTcp();

signals:

public slots:
};

#endif // CFWTCP_H
