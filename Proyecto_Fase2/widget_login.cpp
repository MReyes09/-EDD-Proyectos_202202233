#include "widget_login.h"
#include "ui_widget_login.h"
#include "viewsctr.h"
#include "user_controller.h"

#include <QDebug>
#include <QWidget>
#include <QMessageBox>

Widget_Login::Widget_Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget_Login)
{
    ui->setupUi(this);
}

Widget_Login::~Widget_Login()
{
    delete ui;
}

void Widget_Login::on_btn_Sigin_clicked()
{
    ViewsCtr *viewsCtr = new ViewsCtr();
    QWidget *widgetChange = viewsCtr->getInstanceWidgetSigUp();
    viewsCtr->getInstanceVentanaBase()->cambiarWidgets(widgetChange);

}


void Widget_Login::on_btn_Login_clicked()
{
    QString gmail = ui->txt_correo->text();
    QString pass = ui->txt_pass->text();
    User_Controller* userController = User_Controller::getInstance();
    auto result = userController->logIn(gmail, pass);

    if ( result != nullptr ){
        if( result->getRol() == "Admin" ){
            ViewsCtr *viewsCtr = new ViewsCtr();
            QWidget *widgetChange = viewsCtr->getIntanceWidgetCtrAdmin();
            viewsCtr->getInstanceVentanaBase()->cambiarWidgets(widgetChange);
        }else{
            ViewsCtr *viewsCtr = new ViewsCtr();
            QWidget *widgetChange = viewsCtr->getInstanceWidgetctrUser();
            viewsCtr->getInstanceVentanaBase()->cambiarWidgets(widgetChange);
        }

    }
}

