#include "widgetctradmin.h"
#include "ui_widgetctradmin.h"
#include "viewsctr.h"

#include <QWidget>

WidgetCtrAdmin::WidgetCtrAdmin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetCtrAdmin)
{
    ui->setupUi(this);
}

WidgetCtrAdmin::~WidgetCtrAdmin()
{
    delete ui;
}

void WidgetCtrAdmin::cambiarWidgetAdmin(QWidget* widgetChange)
{
    // Eliminar el widget anterior del layout (si lo hay)
    if (QLayout* layout = ui->wBMenuAdmin->layout()) {
        // Eliminar widgets dentro del layout si ya hay uno
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();  // Borra el widget del layout
            delete item;            // Borra el propio item
        }
        delete layout; // Borra el layout anterior
    }

    // Crear un nuevo layout para widgetBase
    QVBoxLayout* newLayout = new QVBoxLayout(ui->wBMenuAdmin);

    // Añadir el nuevo widget al layout
    newLayout->addWidget(widgetChange);

    // Aplicar el nuevo layout a widgetBase
    ui->wBMenuAdmin->setLayout(newLayout);

    // Actualizar la interfaz gráfica
    ui->wBMenuAdmin->update();
}

void WidgetCtrAdmin::on_pushButton_clicked()
{

    ViewsCtr *viewsCtr = new ViewsCtr();
    QWidget *widgetChange = viewsCtr->getInstanceWidget_CtrUser_Admin();
    cambiarWidgetAdmin(widgetChange);
}


void WidgetCtrAdmin::on_pushButton_4_clicked()
{
    ViewsCtr *viewsCtr = new ViewsCtr();
    QWidget *widgetChange = viewsCtr->getInstanceWidgetLogin();
    viewsCtr->getInstanceVentanaBase()->cambiarWidgets(widgetChange);
}


void WidgetCtrAdmin::on_pushButton_2_clicked()
{
    ViewsCtr *viewsCtr = new ViewsCtr();
    QWidget *widgetChange = viewsCtr->getInstanceWidgetCargasMasivas();
    cambiarWidgetAdmin(widgetChange);
}


void WidgetCtrAdmin::on_pushButton_3_clicked()
{
    ViewsCtr *viewCtr = new ViewsCtr();
    QWidget *widgetChange = viewCtr->getInstanceWidgetReports();
    cambiarWidgetAdmin(widgetChange);
}

