#include "widget_ctruser_admin.h"
#include "ui_widget_ctruser_admin.h"
#include "user_controller.h"
#include "linkedlist.h"
#include "user.h"
#include "avl.h"
#include <QDebug>

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
    ui->tbl_Users->setRowCount(ctrUser->sizeList());
    int index = 0;
    AVL *listUsers = &ctrUser->getListaUsers();

    while(index != ctrUser->sizeList())
    {
        User* usrAddTable =listUsers->at(index);
        ui->tbl_Users->setItem(index, 0, new QTableWidgetItem(usrAddTable->getName()));
        ui->tbl_Users->setItem(index, 1, new QTableWidgetItem(usrAddTable->getLastname()));
        ui->tbl_Users->setItem(index, 2, new QTableWidgetItem(usrAddTable->getEmail()));
        ui->tbl_Users->setItem(index, 3, new QTableWidgetItem(usrAddTable->getBirthdate()));
        index++;
    }

}

void Widget_CtrUser_Admin::on_pushButton_clicked()
{
    QString gmail = ui->txt_buscar->text();
    User_Controller* ctrUser = User_Controller::getInstance();
    User* searchUser = ctrUser->searchUser(gmail);
    if( searchUser != nullptr ){
        ui->tbl_Users->clearContents();
        ui->tbl_Users->setItem(0,0, new QTableWidgetItem(searchUser->getName()));
        ui->tbl_Users->setItem(0,1, new QTableWidgetItem(searchUser->getLastname()));
        ui->tbl_Users->setItem(0,2, new QTableWidgetItem(searchUser->getEmail()));
        ui->tbl_Users->setItem(0,3, new QTableWidgetItem(searchUser->getBirthdate()));
    }else{
        QMessageBox::information(nullptr, "Busqueda de usurio", "El correo proporcionado no corresponde a ningun usaurio");
    }
}


void Widget_CtrUser_Admin::on_btn_Aplicar_clicked()
{
    User_Controller* ctrUser = User_Controller::getInstance();
    QString type_Opcion = ui->cmb_orden->currentText();
    LinkedList* listOrden = new LinkedList();
    if( type_Opcion == "Preorden"){
        ctrUser->avl_preorden(listOrden);
        appendTable(listOrden);
    }else if( type_Opcion == "Inorden" ){
        ctrUser->avl_inorden(listOrden);
        appendTable(listOrden);
    }else{
        ctrUser->avl_posorden(listOrden);
        appendTable(listOrden);
    }
}

void Widget_CtrUser_Admin::appendTable(LinkedList* list)
{
    int index = 0;
    Node *temp = list->head;
    if( list->head == nullptr ){
        ui->tbl_Users->clearContents();
        return;
    }

    ui->tbl_Users->clearContents();
    while (temp != nullptr)
    {
        User* searchUser = temp->user;
        ui->tbl_Users->setItem(index,0, new QTableWidgetItem(searchUser->getName()));
        ui->tbl_Users->setItem(index,1, new QTableWidgetItem(searchUser->getLastname()));
        ui->tbl_Users->setItem(index,2, new QTableWidgetItem(searchUser->getEmail()));
        ui->tbl_Users->setItem(index,3, new QTableWidgetItem(searchUser->getBirthdate()));
        index++;
        temp = temp->next;
    }
}





