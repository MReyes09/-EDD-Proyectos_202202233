#include "adminvew.h"
#include "ui_adminvew.h"
#include "mainview.h"
#include "usuarioswidget.h"

//DEPENDENCIAS DE QT
#include <QMessageBox>
#include <QMdiSubWindow>
#include <QString>

AdminVew::AdminVew(int tipo, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminVew)
{
    setCentralWidget(ui->mdiArea);
    ui->setupUi(this);
}

AdminVew::~AdminVew()
{
    delete ui;
}

void AdminVew::on_actionCarga_De_Usuarios_triggered()
{

}


void AdminVew::on_actionCarga_De_Relaciones_triggered()
{

}


void AdminVew::on_actionCarga_De_Publicaciones_triggered()
{

}


void AdminVew::on_actionSalir_triggered()
{
    close();
}


void AdminVew::on_actionArbol_AVL_Usuarios_triggered()
{

}


void AdminVew::on_actionLista_General_Publicaciones_triggered()
{

}


void AdminVew::on_actionAcerca_De_triggered()
{
    QString mensaje = "Alumno: Matthew Emmanuel Reyes Melgar\nCarnet: 202202233\nCurso: Estructura de Datos";
    QMessageBox::about(this, "Programador", mensaje);
}


void AdminVew::on_actionAdministrar_Usuarios_triggered()
{
    //Configuraciones para mostrar widget dentro de mdiArea y poder manejar multiples vistas
    auto ctrlUsuarios = new UsuariosWidget(this);
    auto subWindow = ui->mdiArea->addSubWindow(ctrlUsuarios);
    subWindow->setGeometry(ctrlUsuarios->geometry());
    subWindow->setWindowTitle(ctrlUsuarios->windowTitle());
    subWindow->show();
}

