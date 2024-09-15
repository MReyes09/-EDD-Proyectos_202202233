#include "widgetperfil.h"
#include "ui_widgetperfil.h"

WidgetPerfil::WidgetPerfil(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetPerfil)
{
    ui->setupUi(this);
}

WidgetPerfil::~WidgetPerfil()
{
    delete ui;
}
