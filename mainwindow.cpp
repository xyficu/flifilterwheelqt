#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_CFW12 = new CFW12();

    if(true == m_CFW12->GetConnStatus())
        ui->labelFLI->setText("FLI Filter Wheel initial successlly!");
    else
        ui->labelFLI->setText("FLI Filter Wheel initial failed!");
    ui->labelFLI->adjustSize();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_CFW12;
}

void MainWindow::on_pushButtonFW1_clicked()
{
    m_CFW12->SetWheelPos(1);
    ui->label_CurPos->setText("1");
}

void MainWindow::on_pushButtonFW2_clicked()
{
    m_CFW12->SetWheelPos(2);
    ui->label_CurPos->setText("2");
}

void MainWindow::on_pushButtonFWHome_clicked()
{
    if(false == m_CFW12->GetConnStatus())
        m_CFW12->InitCFW12();
    else
    {
        m_CFW12->SetWheelPos(0);
        ui->label_CurPos->setText("0");
    }
}
