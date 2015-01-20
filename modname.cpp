#include "modname.h"
#include "ui_modname.h"

ModName::ModName(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModName)
{
    ui->setupUi(this);
}

ModName::~ModName()
{
    delete ui;
}
