#include "usuarioswidget.h"
#include "ui_usuarioswidget.h"

// #include "linkedlist.h"
// #include "user.h"
#include <QString>
#include <QDebug>

UsuariosWidget::UsuariosWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UsuariosWidget)
{
    ui->setupUi(this);
    //std::cout<<"Valor" + to_string(ctrUser->sizeList());
    ctrUser = User_Controller::getInstance();
    // qDebug("Variable: ctrUser");
    // qDebug() << ctrUser->sizeList();
    ui->tableWidgetUsers->setRowCount(ctrUser->sizeList());
    int index = 0;
    while(index != ctrUser->sizeList())
    {
        LinkedList *listUsers = &ctrUser->getListaUsers();
        User* usrAddTable =listUsers->at(index);
        QString id = QString::number(usrAddTable->getIdUser());
        ui->tableWidgetUsers->setItem(index, 0, new QTableWidgetItem(id));
        ui->tableWidgetUsers->setItem(index, 1, new QTableWidgetItem(usrAddTable->getName()));
        ui->tableWidgetUsers->setItem(index, 2, new QTableWidgetItem(usrAddTable->getLastname()));
        ui->tableWidgetUsers->setItem(index, 3, new QTableWidgetItem(usrAddTable->getEmail()));
        ui->tableWidgetUsers->setItem(index, 4, new QTableWidgetItem(usrAddTable->getBirthdate()));
        ui->tableWidgetUsers->setItem(index, 5, new QTableWidgetItem(usrAddTable->getRol()));

        index++;
    }

}


UsuariosWidget::~UsuariosWidget()
{
    delete ui;
    delete ctrUser;
}

