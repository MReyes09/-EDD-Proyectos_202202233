#include "widgetpublicaciones.h"
#include "ui_widgetpublicaciones.h"
#include "user_controller.h"
#include "viewsctr.h"
#include "linkedlistpost.h"

#include <QMessageBox>
#include <QDialog>
#include <QPixmap>

WidgetPublicaciones::WidgetPublicaciones(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetPublicaciones)
    , head(nullptr)
{
    ui->setupUi(this);    
    User_Controller *ctrUser = User_Controller::getInstance();
    head = ctrUser->allPosts->head;
    initialComponents();
}

WidgetPublicaciones::~WidgetPublicaciones()
{
    delete ui;
}

void WidgetPublicaciones::initialComponents()
{
    if( head == nullptr ){
        QMessageBox::information(nullptr, "Busqueda de publicaciones", "No se han encontrado publicaciones!");
        return;
    }
    ui->lbl_gmailPost->setText(head->post->email);
    ui->lbl_FechaPost->setText(head->post->fecha.toString("d/MM/yyyy"));
    ui->txtEdit_ContenidoPost->setText(head->post->contenido);
    if( head->post->pathImage != "" ){
        QPixmap pixmap(head->post->pathImage);

        if (!pixmap.isNull()) {
            // Establece la imagen en el QLabel
            ui->lbl_ImagePost->setPixmap(pixmap);
            ui->lbl_ImagePost->setScaledContents(true); // Escala la imagen para ajustarse al QLabel

        } else {
            // Si la imagen no se carga, muestra un mensaje de error
            ui->lbl_ImagePost->setText("Error al cargar imagen");
        }
    }else{
        ui->lbl_ImagePost->setText("Publicacion sin imgen");
    }

}


void WidgetPublicaciones::on_btn_siguiente_clicked()
{
    if(head == nullptr){
        QMessageBox::information(this, "Publicaciones", "Ya no hay mas publicaciones por ver!");
        return;
    }
    head = head->next;
    if( head != nullptr){
        initialComponents();
    }
}


void WidgetPublicaciones::on_btn_ApliDate_clicked()
{
    QDate fechaSearch = ui->dateEdit->date();
    User_Controller* ctrUser = User_Controller::getInstance();
    ctrUser->searchDateAbb(fechaSearch);
    if(ctrUser->allPosts->head == nullptr){
        QMessageBox::information(this, "Busqueda de publicaciones", "No hay publicaciones en la fecha brindada");
    }else{
        head = ctrUser->allPosts->head;
        initialComponents();
    }

}


void WidgetPublicaciones::on_btn_CrearPost_clicked()
{
    ViewsCtr* viewCtr = new ViewsCtr();
    QDialog *postDialog = viewCtr->getInstanceDialogNewPost();
    postDialog->exec();
    User_Controller* ctrUser = User_Controller::getInstance();
    head = ctrUser->allPosts->head;
    initialComponents();
}


void WidgetPublicaciones::on_btnAplicarOrden_clicked()
{
    User_Controller* ctrUser = User_Controller::getInstance();
    QString type_Opcion = ui->cmbOrden->currentText();
    int cantidad =ui->txtCantidad->text().toInt();
    if( type_Opcion == "Preorden"){
        LinkedListPost* list = ctrUser->preordenPosts(cantidad);
        head = list->head;
        initialComponents();
    }else if( type_Opcion == "Inorden" ){
        LinkedListPost* list = ctrUser->inordenPosts(cantidad);
        head = list->head;
        initialComponents();
    }else{
        LinkedListPost* list = ctrUser->posordenPosts(cantidad);
        head = list->head;
        initialComponents();
    }
}

