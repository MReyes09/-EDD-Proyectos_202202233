#include "dialognewpost.h"
#include "ui_dialognewpost.h"
#include "user_controller.h"

#include "QFileDialog"
#include "QMessageBox"
#include "QPixmap"

DialogNewPost::DialogNewPost(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogNewPost)
{
    ui->setupUi(this);
    setImage();
}

DialogNewPost::~DialogNewPost()
{
    delete ui;
}

void DialogNewPost::on_buttonBox_accepted()
{
    QString contenido = ui->txtEdit_Contenido->toPlainText();
    User_Controller* ctrUser = User_Controller::getInstance();
    ctrUser->addPost(contenido, path);
    accept();

}

void DialogNewPost::on_buttonBox_rejected()
{
    reject();
}

QString DialogNewPost::getPath()
{
    // Abrir el diálogo para elegir archivo
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Cargar Masiva"),    // Título del diálogo
                                                    "",                       // Ruta inicial (directorio actual por defecto)
                                                    tr("Imágenes (*.png *.jpg *.jpeg *.bmp *.gif);;Todos los archivos (*.*)") // Filtros de archivo
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

void DialogNewPost::on_btn_setImage_clicked()
{
    path = getPath();
    setImage();
}

void DialogNewPost::setImage(){
    QPixmap pixmap(path);

    if (!pixmap.isNull()) {
        // Establece la imagen en el QLabel
        ui->lbl_image->setPixmap(pixmap);
        ui->lbl_image->setScaledContents(true); // Escala la imagen para ajustarse al QLabel

    } else {
        // Si la imagen no se carga, muestra un mensaje de error
        ui->lbl_image->setText("No se pudo cargar la imagen.");
    }
}

