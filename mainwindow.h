#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QDateTime>
#include <QDate>
#include "cfw12.h"
#include "about.h"
#include "cfwthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonFW1_clicked();

    void on_pushButtonFW2_clicked();

    void on_pushButtonFWHome_clicked();

    void on_pushButtonFW3_clicked();

    void on_pushButtonFW4_clicked();

    void on_pushButtonFW5_clicked();

    void on_pushButtonFW6_clicked();

    void on_pushButtonFW7_clicked();

    void on_pushButtonFW8_clicked();

    void on_pushButtonFW9_clicked();

    void on_pushButtonFW10_clicked();

    void on_pushButtonFW11_clicked();

    void UpdateStatus();

    void on_action_Exit_triggered();

    void on_action_About_triggered();



private:
    Ui::MainWindow *ui;
    CFW12 *m_CFW12;
    QTimer *m_timer;
    QTime m_time;
    QDate m_date;
    QDateTime m_dateTime;
    void SetFWPos(long pos);
    CFWThread m_cfw;
    char *libVer;

signals:
    void MainGetWPos(long &pos);
    void MainSetWPos(long pos);
    void MainGetWStatus(long &status);
    void MainGetWLibVer(char **libVer);
    void MainGetWConStatus(bool &conStatus);

};

#endif // MAINWINDOW_H
