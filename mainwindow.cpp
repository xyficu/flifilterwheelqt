#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //set window tilte
    setWindowTitle("FLI CFW12 Controller");

    //initial timer
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), SLOT(UpdateStatus()));
    m_timer->start(100);

    //initial CFW
    m_CFW12 = new CFW12();
    ui->label_libVer->setText(m_CFW12->GetLibVer());
    ui->label_libVer->adjustSize();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_CFW12;
}

void MainWindow::SetFWPos(long pos)
{
    if(true == m_CFW12->GetConnStatus())
    {
        m_CFW12->SetWheelPos(pos);
        ui->label_CurPos->setText(QString::number(pos));
    }
}

void MainWindow::on_pushButtonFW1_clicked()
{
    SetFWPos(1);
}

void MainWindow::on_pushButtonFW2_clicked()
{
    SetFWPos(2);
}

void MainWindow::on_pushButtonFWHome_clicked()
{
    SetFWPos(0);
}

void MainWindow::on_pushButtonFW3_clicked()
{
    SetFWPos(3);
}

void MainWindow::on_pushButtonFW4_clicked()
{
    SetFWPos(4);
}

void MainWindow::on_pushButtonFW5_clicked()
{
    SetFWPos(5);
}

void MainWindow::on_pushButtonFW6_clicked()
{
    SetFWPos(6);
}

void MainWindow::on_pushButtonFW7_clicked()
{
    SetFWPos(7);
}

void MainWindow::on_pushButtonFW8_clicked()
{
    SetFWPos(8);
}

void MainWindow::on_pushButtonFW9_clicked()
{
    SetFWPos(9);
}

void MainWindow::on_pushButtonFW10_clicked()
{
    SetFWPos(10);
}

void MainWindow::on_pushButtonFW11_clicked()
{
    SetFWPos(11);
}

void MainWindow::UpdateStatus()
{
    //try to connect the fliter wheel per 100ms
    if(false == m_CFW12->GetConnStatus())
        m_CFW12->InitCFW12();

    //try to update status per 100ms
    long pos=0;
    if(true == m_CFW12->GetConnStatus())
    {
        ui->labelFLI->setText("FLI Filter Wheel connected!");
//        if(2 == m_CFW12->GetStatus())
//            ui->label_Status->setText("Moving...");
//        else
//            ui->label_Status->setText("Stopped");
        m_CFW12->GetWheelPos(pos);
        ui->label_CurPos->setText(QString::number(pos));
    }
    else
        ui->labelFLI->setText("FLI Filter Wheel not connected!");

    //update time
    m_dateTime.setTime(m_time.currentTime());
    m_dateTime.setDate(m_date.currentDate());
    QString currentDateTime = m_dateTime.toString("yyyy-mm-dd hh:mm:ss");
    ui->label_time->setText(currentDateTime);
    ui->label_time->adjustSize();

    //adjust label size
    ui->labelFLI->adjustSize();
//    ui->label_Status->adjustSize();
    ui->label_CurPos->adjustSize();

}

void MainWindow::on_action_Exit_triggered()
{
    QApplication::exit(0);
}

void MainWindow::on_action_About_triggered()
{
    About a(this);
    a.exec();
}
