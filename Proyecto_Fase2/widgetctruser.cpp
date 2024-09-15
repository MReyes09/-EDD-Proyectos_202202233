#include "widgetctruser.h"
#include "ui_widgetctruser.h"
#include "viewsctr.h"
#include <QWidget>

WidgetctrUser::WidgetctrUser(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetctrUser)
{
    ui->setupUi(this);
}

WidgetctrUser::~WidgetctrUser()
{
    delete ui;
}

void WidgetctrUser::on_btnCerrarSesion_clicked()
{
    ViewsCtr* viewsCtr = new ViewsCtr();
    QWidget* widgetChange = viewsCtr->getInstanceWidgetLogin();
    viewsCtr->getInstanceVentanaBase()->cambiarWidgets(widgetChange);
}

void WidgetctrUser::on_btn_Perfil_clicked()
{
    ViewsCtr* viewsCtr = new ViewsCtr();
    QWidget* widgetChange = viewsCtr->getInstanceWidgetPerfil();
    cambiarWidget(widgetChange);
}

void WidgetctrUser::cambiarWidget(QWidget* widgetChange)
{
    // Eliminar el widget anterior del layout (si lo hay)
    if (QLayout* layout = ui->widgetBase->layout()) {
        // Eliminar widgets dentro del layout si ya hay uno
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();  // Borra el widget del layout
            delete item;            // Borra el propio item
        }
        delete layout; // Borra el layout anterior
    }

    // Crear un nuevo layout para widgetBase
    QVBoxLayout* newLayout = new QVBoxLayout(ui->widgetBase);

    // Añadir el nuevo widget al layout
    newLayout->addWidget(widgetChange);

    // Aplicar el nuevo layout a widgetBase
    ui->widgetBase->setLayout(newLayout);

    // Actualizar la interfaz gráfica
    ui->widgetBase->update();
}

void WidgetctrUser::on_btn_WPost_clicked()
{

    ViewsCtr* viewsCtr = new ViewsCtr();
    QWidget* widgetChange = viewsCtr->getInstanceWidgetPost();
    cambiarWidget(widgetChange);
}

