#include "widgetreports.h"
#include "ui_widgetreports.h"
#include "user_controller.h"
#include "dialog_reporte.h"

WidgetReports::WidgetReports(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetReports)
{
    ui->setupUi(this);
}

WidgetReports::~WidgetReports()
{
    delete ui;
}

void WidgetReports::on_pushButton_2_clicked()
{
    User_Controller* ctrUser = User_Controller::getInstance();
    ctrUser->report_Posts();

    // Crear una instancia del diálogo y ejecutarlo
    Dialog_Reporte* dialog = new Dialog_Reporte(this, "C:/Users/matth/OneDrive/Documentos/Proyectos C++/EDD_Proyectos_202202233/Proyecto_Fase2/report/posts.png");
    dialog->exec(); // Mostrar el diálogo de forma modal

}

