#include "ventanabase.h"
#include "widget_login.h"
#include <QMessageBox>

VentanaBase* VentanaBase::instance = nullptr;

VentanaBase* VentanaBase::getInstance()
{
    if (!instance)
    {
        instance = new VentanaBase();
    }
    return instance;
}

VentanaBase::VentanaBase(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::VentanaBase)
{
    initComponents();
}

VentanaBase::~VentanaBase()
{
    delete ui;
}

void VentanaBase::initComponents()
{
    ui->setupUi(this); // Configura la interfaz gráfica
    Widget_Login *widgetLogin = new Widget_Login();
    cambiarWidgets(widgetLogin);
}

void VentanaBase::cambiarWidgets(QWidget *widgetChange)
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

void VentanaBase::on_actionAcerca_De_triggered()
{
    QString mensaje = "Alumno: Matthew Emmanuel Reyes Melgar\nCarnet: 202202233\nCurso: Estructura de Datos";
    QMessageBox::about(this, "Programador", mensaje);
}

