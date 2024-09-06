#include "registerview.h"
#include "ui_registerview.h"

registerView::registerView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::registerView)
{
    ui->setupUi(this);
}

registerView::~registerView()
{
    delete ui;
}

void registerView::on_buttonBox_accepted()
{

}


void registerView::on_buttonBox_rejected()
{

}

