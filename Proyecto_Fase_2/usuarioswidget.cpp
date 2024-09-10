#include "usuarioswidget.h"
#include "ui_usuarioswidget.h"

UsuariosWidget::UsuariosWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UsuariosWidget)
{
    ui->setupUi(this);
    //mTable = new TableModelUser(this);
    ctrUser = User_Controller::getInstance();
}

UsuariosWidget::~UsuariosWidget()
{
    delete ui;
    //delete mTable;
}
