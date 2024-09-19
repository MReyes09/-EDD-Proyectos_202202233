#include "widgetsolicitudes.h"
#include "ui_widgetsolicitudes.h"
#include "user_controller.h"
#include "Node_Sol.h"
#include "Solicitud.h"
#include "user.h"
#include "avl.h"
#include <QDebug>

WidgetSolicitudes::WidgetSolicitudes(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetSolicitudes)
{
    ui->setupUi(this);
    initComponents();
}

WidgetSolicitudes::~WidgetSolicitudes()
{
    delete ui;
}


void WidgetSolicitudes::initComponents(){

    User_Controller *ctrUser = User_Controller::getInstance();
    ctrUser->listDesconocidos();
    User* User_Logued = ctrUser->User_Logued;

    //TABLA DE SOLICITUDES RECIBIDAS
    ui->tblSolRec->setRowCount(User_Logued->getListSol().contador);
    Node_Sol* head = User_Logued->getListSol().head;
    int index = 0;
    while(head != nullptr)
    {
        Solicitud* solicitud = head->solicitud;
        ui->tblSolRec->setItem(index, 0, new QTableWidgetItem(solicitud->getCorreoEmisor()));
        head = head->next;
        index++;
    }

    //TABLA DE SOLICITUDES ENVIADAS
    head = User_Logued->getListEnvios().head;
    int contador = 0;
    while (head != nullptr){
        contador ++;
        head = head->next;
    }
    ui->tblSolEnv->setRowCount(contador);
    head = User_Logued->getListEnvios().head;
    index = 0;
    while(head != nullptr)
    {
        Solicitud* solicitud = head->solicitud;
        ui->tblSolEnv->setItem(index, 0, new QTableWidgetItem(solicitud->getCorreoReceptor()));
        head = head->next;
        index++;
    }

    //TABLA DE USUARIOS DESCONOCIDOS
    AVL* listDesconocidos = ctrUser->getListaNoAmigos();
    ui->tblUsuarios->setRowCount(listDesconocidos->size_List());
    index = 0;

    while(index != listDesconocidos->size_List())
    {
        User* usrAddTable =listDesconocidos->at(index);
        ui->tblUsuarios->setItem(index, 0, new QTableWidgetItem(usrAddTable->getName()));
        ui->tblUsuarios->setItem(index, 1, new QTableWidgetItem(usrAddTable->getLastname()));
        ui->tblUsuarios->setItem(index, 2, new QTableWidgetItem(usrAddTable->getEmail()));
        ui->tblUsuarios->setItem(index, 3, new QTableWidgetItem(usrAddTable->getBirthdate()));
        index++;
    }

}
