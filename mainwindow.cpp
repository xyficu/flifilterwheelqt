#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

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

    //start the cfw thread
    m_cfw.start();

    //connect filterwheel signals
    connect(this, SIGNAL(MainGetWPos(long &)), &m_cfw, SLOT(GetWPos(long &)), Qt::DirectConnection);
    connect(this, SIGNAL(MainSetWPos(long)), &m_cfw, SLOT(SetWPos(long)));
    connect(this, SIGNAL(MainGetWStatus(long &)), &m_cfw, SLOT(GetWStatus(long &)), Qt::DirectConnection);
    connect(this, SIGNAL(MainGetWLibVer(char**)), &m_cfw, SLOT(GetLibVer(char**)), Qt::DirectConnection);
    connect(this, SIGNAL(MainGetWConStatus(bool&)), &m_cfw, SLOT(GetWConStatus(bool&)), Qt::DirectConnection);

}

MainWindow::~MainWindow()
{
    delete ui;
    m_cfw.stop();
    m_cfw.wait();
}

void MainWindow::SetFWPos(long pos)
{
    if(true == m_CFW12->GetConnStatus())
    {
        m_CFW12->SetWheelPos(pos);
        ui->label_CurPos->setText(QString::number(pos));
    }
}


void MainWindow::on_pushButtonFWHome_clicked()
{
    emit MainSetWPos(0);
}

void MainWindow::on_pushButtonFW1_clicked()
{
    emit MainSetWPos(1);
}

void MainWindow::on_pushButtonFW2_clicked()
{
    emit MainSetWPos(2);
}

void MainWindow::on_pushButtonFW3_clicked()
{
    emit MainSetWPos(3);
}

void MainWindow::on_pushButtonFW4_clicked()
{
    emit MainSetWPos(4);
}

void MainWindow::on_pushButtonFW5_clicked()
{
    emit MainSetWPos(5);
}

void MainWindow::on_pushButtonFW6_clicked()
{
    emit MainSetWPos(6);
}

void MainWindow::on_pushButtonFW7_clicked()
{
    emit MainSetWPos(7);
}

void MainWindow::on_pushButtonFW8_clicked()
{
    emit MainSetWPos(8);
}

void MainWindow::on_pushButtonFW9_clicked()
{
    emit MainSetWPos(9);
}

void MainWindow::on_pushButtonFW10_clicked()
{
    emit MainSetWPos(10);
}

void MainWindow::on_pushButtonFW11_clicked()
{
    emit MainSetWPos(11);
}

void MainWindow::UpdateStatus()
{
    //get the fliter wheel sdk version
    emit MainGetWLibVer(&libVer);
    ui->label_libVer->setText(libVer);
    ui->label_libVer->adjustSize();

    //update connection status
    long pos=0;    
    bool conStatus = true;
    emit MainGetWConStatus(conStatus);
    if(true == conStatus)
    {
        ui->labelFLI->setText("FLI Filter Wheel connected!");

        emit MainGetWPos(pos);
        ui->label_CurPos->setText(QString::number(pos));
    }
    else
        ui->labelFLI->setText("FLI Filter Wheel not connected!");

    //update moving status
//    long status=0;
//    emit MainGetWStatus(status);
//    if(0!=status)
//        ui->label_CurStatus->setText("Moving...");
//    else
//        ui->label_CurStatus->setText("Stopped.");

    //update time
    m_dateTime.setTime(m_time.currentTime());
    m_dateTime.setDate(m_date.currentDate());
    QString currentDateTime = m_dateTime.toString("yyyy-mm-dd hh:mm:ss");
    ui->label_time->setText(currentDateTime);
    ui->label_time->adjustSize();

    //adjust label size
    ui->labelFLI->adjustSize();
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


