#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "registerview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_Login_clicked()
{

}


void MainWindow::on_btn_Sigin_clicked()
{
    registerView d(this);
    if(d.exec() == QDialog::Rejected) {
        return;
    }

}

