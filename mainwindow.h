#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cfw12.h"

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

private:
    Ui::MainWindow *ui;
    CFW12 *m_CFW12;
};

#endif // MAINWINDOW_H
