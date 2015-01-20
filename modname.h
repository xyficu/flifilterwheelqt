#ifndef MODNAME_H
#define MODNAME_H

#include <QDialog>

namespace Ui {
class ModName;
}

class ModName : public QDialog
{
    Q_OBJECT

public:
    explicit ModName(QWidget *parent = 0);
    ~ModName();

private:
    Ui::ModName *ui;
};

#endif // MODNAME_H
