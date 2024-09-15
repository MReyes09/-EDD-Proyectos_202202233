#ifndef DIALOG_REPORTE_H
#define DIALOG_REPORTE_H

#include <QDialog>
#include <string>

using namespace std;

namespace Ui {
class Dialog_Reporte;
}

class Dialog_Reporte : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Reporte(QWidget *parent = nullptr, const string& path = "" );
    ~Dialog_Reporte();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog_Reporte *ui;
    QString imagePath; // Almacena la ruta de la imagen como QString
};

#endif // DIALOG_REPORTE_H
