#include "widget_ctruser_admin.h"
#include "ui_widget_ctruser_admin.h"
#include "user_controller.h"
#include "user.h"
#include "avl.h"

Widget_CtrUser_Admin::Widget_CtrUser_Admin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget_CtrUser_Admin)
{
    ui->setupUi(this);
    initComponents();
}

Widget_CtrUser_Admin::~Widget_CtrUser_Admin()
{
    delete ui;
}


void Widget_CtrUser_Admin::initComponents()
{
    User_Controller *ctrUser = User_Controller::getInstance();

    //Agrego una cantidad de filas que corresponde a la cantidad de usuarios en el sistema
    ui->tableWidget->setRowCount(ctrUser->sizeList());
    int index = 0;
    AVL *listUsers = &ctrUser->getListaUsers();

    while(index != ctrUser->sizeList())
    {
        User* usrAddTable =listUsers->at(index);
        ui->tableWidget->setItem(index, 0, new QTableWidgetItem(usrAddTable->getName()));
        ui->tableWidget->setItem(index, 1, new QTableWidgetItem(usrAddTable->getLastname()));
        ui->tableWidget->setItem(index, 2, new QTableWidgetItem(usrAddTable->getEmail()));
        ui->tableWidget->setItem(index, 3, new QTableWidgetItem(usrAddTable->getBirthdate()));
        index++;
    }

}
