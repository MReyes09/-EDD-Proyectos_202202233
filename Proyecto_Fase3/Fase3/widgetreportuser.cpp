#include "widgetreportuser.h"
#include "ui_widgetreportuser.h"
#include "user_controller.h"
#include "NodePost.h"
#include "publicacion.h"

#include <QPixmap>

widgetReportUser::widgetReportUser(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::widgetReportUser)
    , head(nullptr)
{
    ui->setupUi(this);
    User_Controller *ctrUser = User_Controller::getInstance();
    ctrUser->allPosts->ordenList();
    head = ctrUser->allPosts->head;
    initComponents();
}

widgetReportUser::~widgetReportUser()
{
    delete ui;
}

void widgetReportUser::initComponents()
{
    //Tabla Reporte2
    User_Controller *ctrUser = User_Controller::getInstance();

    //Agrego una cantidad de filas que corresponde a la cantidad de usuarios en el sistema
    ui->tbl_Report2->setRowCount(3);
    int index = 0;
    NodePost* tempPost = ctrUser->allPosts->head;

    while(tempPost != nullptr && index <= 3)
    {
        Publicacion* usrAddTable = tempPost->post;
        ui->tbl_Report2->setItem(index, 0, new QTableWidgetItem(usrAddTable->fecha.toString("d/MM/yyyy")));
        ui->tbl_Report2->setItem(index, 1, new QTableWidgetItem(usrAddTable->email));
        ui->tbl_Report2->setItem(index, 2, new QTableWidgetItem(QString::number(usrAddTable->No_Comentarios)));
        index++;
        tempPost = tempPost->next;
    }

    vector<FechaPublicacion> topFechas = ctrUser->arbolBBusqueda->topTresFechas();
    index = 0;
    ui->tbl_Report1->setRowCount(3);
    for (const auto& entry : topFechas) {
        ui->tbl_Report1->setItem(index, 0, new QTableWidgetItem(entry.fecha.toString("dd/MM/yyyy")));
        ui->tbl_Report1->setItem(index, 1, new QTableWidgetItem(QString::number(entry.cantidad)));
        index++;
    }

    ui->lbl_Image->setText("No hay ninguna imagen cargada, genera una");


}

void widgetReportUser::on_pushButton_clicked()
{
    QString path = "C:/Users/matth/OneDrive/Documentos/Proyectos C++/EDD_Proyectos_202202233/Proyecto_Fase2/report/abbDate.png";
    User_Controller* ctrUser = User_Controller::getInstance();
    QDate dateG = ui->datePost->date();
    ctrUser->arbolBBusqueda->graphDate(dateG);

    QPixmap pixmap(path);

    if (!pixmap.isNull()) {
        // Establece la imagen en el QLabel
        ui->lbl_Image->setPixmap(pixmap);
        ui->lbl_Image->setScaledContents(true); // Escala la imagen para ajustarse al QLabel

    } else {
        // Si la imagen no se carga, muestra un mensaje de error
        ui->lbl_Image->setText("No se pudo cargar la imagen.");
    }
}

