#include "mainview.h"
#include "ui_mainview.h"
#include "user_controller.h"

mainView::mainView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::mainView)
{
    ui->setupUi(this);
}

mainView::~mainView()
{
    delete ui;
}

void mainView::on_btn_Login_clicked()
{
    QString gmail = ui->txt_correo_2->text();
    QString pass = ui->txt_pass->text();
    User_Controller* userController = User_Controller::getInstance();
    auto result = userController->logIn(gmail, pass);

    if ( result != nullptr ){
        //if( result->getRol() == "Admin" ){
        //Opciones de administrador
        //}else{
        //Opciones de usuario
        //}

    }
    accept();
}


void mainView::on_btn_Sigin_clicked()
{
    registerView d(this);
    if( d.exec() == QDialog::Rejected ) {
        return;
    }
}

