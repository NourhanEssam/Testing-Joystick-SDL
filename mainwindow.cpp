#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    a = new joysticksdl(0);
    a->setKind(1,4);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    a->ShowAvailableJoysticks();
}

void MainWindow::on_pushButton_2_clicked()
{
    a->ShowJoystickData();
}
