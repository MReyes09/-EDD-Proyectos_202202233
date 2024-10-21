#include "widgetperfil.h"
#include "ui_widgetperfil.h"

#include "user_controller.h"
#include "user.h"

#include <QDate>

WidgetPerfil::WidgetPerfil(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetPerfil)
{
    ui->setupUi(this);
    initComponents();
}

WidgetPerfil::~WidgetPerfil()
{
    delete ui;
}

void WidgetPerfil::initComponents(){
    User_Controller *ctrUser = User_Controller::getInstance();
    User* user_logued = ctrUser->User_Logued;

    ui->txt_nombre->setText(user_logued->getName());
    ui->txt_Apellidos->setText(user_logued->getLastname());
    ui->txt_Correo->setText(user_logued->getEmail());
    ui->txt_Pass->setText(user_logued->getPassword());
    ui->birthDay->setDate(QDate::fromString(user_logued->getBirthdate(), "yyyy/MM/d"));

}

void WidgetPerfil::on_btn_UpdateData_clicked()
{

    QString nombre = ui->txt_nombre->text();
    QString apellidos = ui->txt_Apellidos->text();
    QString pass = ui->txt_Pass->text();
    QString birthDay = ui->birthDay->text();

    User_Controller *ctrUser = User_Controller::getInstance();
    ctrUser->ActualizarUser(nombre, apellidos, birthDay, pass);


}

