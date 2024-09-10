#ifndef ADMINVEW_H
#define ADMINVEW_H

#include <QMainWindow>

namespace Ui {
class AdminVew;
}

class AdminVew : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminVew(int tipo, QWidget *parent = nullptr);
    ~AdminVew();

private slots:
    void on_actionCarga_De_Usuarios_triggered();

    void on_actionCarga_De_Relaciones_triggered();

    void on_actionCarga_De_Publicaciones_triggered();

    void on_actionSalir_triggered();

    void on_actionArbol_AVL_Usuarios_triggered();

    void on_actionLista_General_Publicaciones_triggered();

    void on_actionAcerca_De_triggered();

    void on_actionAdministrar_Usuarios_triggered();

private:
    Ui::AdminVew *ui;
};

#endif // ADMINVEW_H
