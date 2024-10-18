#include "widgetsolicitudes.h"
#include "ui_widgetsolicitudes.h"
#include "user_controller.h"
#include "Node_Sol.h"
#include "Solicitud.h"
#include "user.h"
#include "avl.h"
#include <QDebug>
#include <QPushButton>
#include <QHBoxLayout>

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

    ui->tblSolEnv->clearContents();
    ui->tblSolRec->clearContents();
    ui->tblUsuarios->clearContents();

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

        if( index ==0 ){
            // Crear botones de Aceptar y Rechazar
            QPushButton* btnAceptar = new QPushButton("Aceptar");
            QPushButton* btnRechazar = new QPushButton("Rechazar");

            // Agregar los botones a la tabla
            QWidget* cellWidget = new QWidget();
            QHBoxLayout* layout = new QHBoxLayout(cellWidget);
            layout->addWidget(btnAceptar);
            layout->addWidget(btnRechazar);
            layout->setAlignment(Qt::AlignCenter);
            cellWidget->setLayout(layout);
            ui->tblSolRec->setCellWidget(index, 1, cellWidget);  // Colocar en la segunda columna

            // Conectar el botón Aceptar
            connect(btnAceptar, &QPushButton::clicked, this, [=]() {

                aceptarSolicitud(index);  // Función que maneja aceptar solicitud
            });

            // Conectar el botón Rechazar
            connect(btnRechazar, &QPushButton::clicked, this, [=]() {

                rechazarSolicitud(index);  // Función que maneja rechazar solicitud
            });
        }

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
        // Crear botones de Aceptar y Rechazar
        QPushButton* btnCancelar = new QPushButton("Cancelar");
        // Agregar los botones a la tabla
        QWidget* cellWidget = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout(cellWidget);

        layout->addWidget(btnCancelar);
        layout->setAlignment(Qt::AlignCenter);
        cellWidget->setLayout(layout);
        ui->tblSolEnv->setCellWidget(index, 1, cellWidget);  // Colocar en la segunda columna
        // Conectar el botón Rechazar
        connect(btnCancelar, &QPushButton::clicked, this, [=]() {

            cancelarSolicitud(index);  // Función que maneja rechazar solicitud
        });

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
        // Crear botones de Aceptar y Rechazar
        QPushButton* btnEnviar = new QPushButton("Enviar Solicitud");
        // Agregar los botones a la tabla
        QWidget* cellWidget = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout(cellWidget);

        layout->addWidget(btnEnviar);
        layout->setAlignment(Qt::AlignCenter);
        cellWidget->setLayout(layout);
        ui->tblUsuarios->setCellWidget(index, 4, cellWidget);
        // Conectar el botón Rechazar
        connect(btnEnviar, &QPushButton::clicked, this, [=]() {

            enviarSolicitud(index);  // Función que maneja rechazar solicitud
        });

        index++;
    }
}


void WidgetSolicitudes::aceptarSolicitud(int row)
{
    User_Controller *ctrUser = User_Controller::getInstance();
    ctrUser->solicitudes(1);
    initComponents();
}

void WidgetSolicitudes::rechazarSolicitud(int row)
{
    User_Controller *ctrUser = User_Controller::getInstance();
    ctrUser->solicitudes(0);
    initComponents();
}

void WidgetSolicitudes::cancelarSolicitud(int row)
{
    QTableWidgetItem* item = ui->tblSolEnv->item(row, 0);
    QString email_friend = item->text();
    User_Controller* ctrUser = User_Controller::getInstance();
    ctrUser->cancelarSolicitud(email_friend);
    initComponents();
}

void WidgetSolicitudes::enviarSolicitud(int row)
{
    QTableWidgetItem* item = ui->tblUsuarios->item(row, 2);
    QString email_friend = item->text();
    User_Controller* ctrUser = User_Controller::getInstance();
    ctrUser->solicitud_Amistad(email_friend);
    initComponents();
}

