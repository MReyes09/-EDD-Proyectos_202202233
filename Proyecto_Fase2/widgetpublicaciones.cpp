#include "widgetpublicaciones.h"
#include "ui_widgetpublicaciones.h"

WidgetPublicaciones::WidgetPublicaciones(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetPublicaciones)
{
    ui->setupUi(this);
}

WidgetPublicaciones::~WidgetPublicaciones()
{
    delete ui;
}
