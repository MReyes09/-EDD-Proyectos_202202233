#include "widget_sigup.h"
#include "ui_widget_sigup.h"
#include "viewsctr.h"
#include "user_controller.h"

Widget_SigUp::Widget_SigUp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget_SigUp)
{
    ui->setupUi(this);
}

Widget_SigUp::~Widget_SigUp()
{
    delete ui;
}

void Widget_SigUp::on_buttonBox_accepted()
{
    QString name_ = ui->txt_name->text();
    QString lastname_ = ui->txt_lastname->text();
    QString email_ = ui->txt_correo->text();
    QString password_ = ui->txt_pass->text();
    QString birthdate_ = ui->date_birthday->text();

    // Obtener la instancia de User_Controller
    User_Controller* userController = User_Controller::getInstance();
    bool result = userController->sigIn(name_, lastname_, email_, password_, birthdate_, "User");
    if( result ){
        //Realizar cambio de ventana a login
        ViewsCtr *viewsCtr = new ViewsCtr();
        QWidget *widgetChange = viewsCtr->getInstanceWidgetLogin();
        viewsCtr->getInstanceVentanaBase()->cambiarWidgets(widgetChange);
    }
}


void Widget_SigUp::on_buttonBox_rejected()
{
    ViewsCtr *viewsCtr = new ViewsCtr();
    QWidget *widgetChange = viewsCtr->getInstanceWidgetLogin();
    viewsCtr->getInstanceVentanaBase()->cambiarWidgets(widgetChange);

}

