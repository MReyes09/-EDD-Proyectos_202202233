#include "dialog_reporte.h"
#include "ui_dialog_reporte.h"
#include <QPixmap>

using namespace std;

Dialog_Reporte::Dialog_Reporte(QWidget *parent, const string& path)
    : QDialog(parent)
    , ui(new Ui::Dialog_Reporte)
    , imagePath(QString::fromStdString(path)) // Convierte el string a QString
{
    ui->setupUi(this);

    QPixmap pixmap(imagePath);

    if (!pixmap.isNull()) {
        // Establece la imagen en el QLabel
        ui->label_2->setPixmap(pixmap);
        ui->label_2->setScaledContents(true); // Escala la imagen para ajustarse al QLabel

    } else {
        // Si la imagen no se carga, muestra un mensaje de error
        ui->label_2->setText("No se pudo cargar la imagen.");
    }
}

Dialog_Reporte::~Dialog_Reporte()
{
    delete ui;
}


void Dialog_Reporte::on_pushButton_clicked()
{
    reject();
}

