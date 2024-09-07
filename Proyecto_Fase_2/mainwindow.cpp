
//Dependencias
#include <QString>

//Archivos del proyecto
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "user_controller.h"

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
    QString gmail = ui->txt_correo->text();
    QString pass = ui->txt_pass->text();
    User_Controller* userController = User_Controller::getInstance();
    auto result = userController->logIn(gmail, pass);

    if ( result != nullptr ){
        if( result->getRol() == "Admin" ){
            //Opciones de administrador
        }else{
            //Opciones de usuario
        }
    }

}


void MainWindow::on_btn_Sigin_clicked()
{
    registerView d(this);
    if( d.exec() == QDialog::Rejected ) {
        return;
    }
}

