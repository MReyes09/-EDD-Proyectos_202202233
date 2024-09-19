#include "widgetbuscaruser.h"
#include "ui_widgetbuscaruser.h"
#include "user_controller.h"
#include "user.h"
#include "QMessageBox"

WidgetBuscarUser::WidgetBuscarUser(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetBuscarUser)
{
    ui->setupUi(this);
}

WidgetBuscarUser::~WidgetBuscarUser()
{
    delete ui;
}

void WidgetBuscarUser::on_pushButton_clicked()
{
    User_Controller* ctrUser = User_Controller::getInstance();
    QString correoSearch = ui->lineEdit_correo->text();

    User* userFind = ctrUser->searchUser(correoSearch);
    if (userFind == nullptr){
        QMessageBox::information(this, "Busqueda de usuario", "El correo brindado no corresponde a ningun usuario");
        return;
    }

    ui->txt_correo->setText(userFind->getEmail());
    ui->txt_lastname->setText(userFind->getLastname());
    ui->txt_name->setText(userFind->getName());
    ui->txt_date_birthday->setText(userFind->getBirthdate());
}

