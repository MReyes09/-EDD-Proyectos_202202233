#include "widgetcargasmasivas.h"
#include "ui_widgetcargasmasivas.h"
#include "user_controller.h"

#include <QString>
#include <QMessageBox>
#include <QMdiSubWindow>
#include <QFileDialog>
#include <QDebug>

WidgetCargasMasivas::WidgetCargasMasivas(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetCargasMasivas)
{
    ui->setupUi(this);
}

WidgetCargasMasivas::~WidgetCargasMasivas()
{
    delete ui;
}

void WidgetCargasMasivas::on_pushButton_clicked()
{
    QString path = get_Path();
    User_Controller *ctrUser = User_Controller::getInstance();
    if(path != "" )
    {
        bool result = ctrUser->carga_Usuarios(path);
        if( result )
        {
            QMessageBox::information(this, "Carga De Usuarios", "La carga de usuarios fue hecha correctamente");
        }else{
            QMessageBox::warning(this, "Carga De Usuarios", "Ha ocurrido un error en la carga de usuarios");
        }
    }
}

QString WidgetCargasMasivas::get_Path()
{
    // Abrir el diálogo para elegir archivo
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Cargar Masiva"),    // Título del diálogo
                                                    "",                       // Ruta inicial (directorio actual por defecto)
                                                    tr("Archivos CSV (*.csv);;Todos los archivos (*.*)") // Filtros de archivo
                                                    );

    // Verificar si se seleccionó un archivo
    if (!fileName.isEmpty()) {
        return fileName;
    }
    else {
        // El usuario no seleccionó ningún archivo
        QMessageBox::warning(this, tr("Advertencia"), tr("No se seleccionó ningún archivo."));
    }

    return nullptr;
}

void WidgetCargasMasivas::on_pushButton_2_clicked()
{
    QString path = get_Path();
    User_Controller *ctrUser = User_Controller::getInstance();
    if(path != "")
    {
        bool result = ctrUser->carga_Solicitudes(path);
        if( result )
        {
            QMessageBox::information(this, "Carga De Solicitudes", "La carga de solicitudes fue hecha correctamente");
        }else{
            QMessageBox::warning(this, "Carga De Solicitudes", "Ha ocurrido un error en la carga de solicitudes");
        }
    }
}

void WidgetCargasMasivas::on_pushButton_3_clicked()
{
    QString path = get_Path();
    User_Controller *ctrUser = User_Controller::getInstance();
    if(path != "")
    {
        bool result = ctrUser->carga_Post(path);
        if( result )
        {
            QMessageBox::information(this, "Carga De Publicaciones", "La carga de publicaciones fue hecha correctamente");
        }else{
            QMessageBox::warning(this, "Carga De Publicaciones", "Ha ocurrido un error en la carga de publicaciones");
        }
    }
}

