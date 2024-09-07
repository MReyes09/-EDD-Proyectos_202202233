#include <QString>

#include "registerview.h"
#include "ui_registerview.h"
#include "user_controller.h"

registerView::registerView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::registerView)
{
    ui->setupUi(this);
}

registerView::~registerView()
{
    delete ui;
}

void registerView::on_buttonBox_accepted()
{
    QString name_ = ui->txt_name->text();
    QString lastname_ = ui->txt_lastname->text();
    QString email_ = ui->txt_correo->text();
    QString password_ = ui->txt_pass->text();
    QString birthdate_ = ui->date_birthday->text();

    // Obtener la instancia de User_Controller
    User_Controller* userController = User_Controller::getInstance();
    userController->sigIn(name_, lastname_, email_, password_, birthdate_, "User");
    accept();

}


void registerView::on_buttonBox_rejected()
{
    reject();
}

