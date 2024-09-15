#ifndef VENTANABASE_H
#define VENTANABASE_H

#include <QMainWindow>
#include <QWidget>
#include "ui_ventanabase.h" // Archivo generado por Qt Designer

class VentanaBase : public QMainWindow
{
    Q_OBJECT

public:
    static VentanaBase* getInstance(); // Método para obtener la instancia única
    void cambiarWidgets(QWidget *widgetChange);

private slots:
    void on_actionAcerca_De_triggered();

private:
    VentanaBase(QWidget *parent = nullptr); // Constructor privado
    ~VentanaBase(); // Destructor privado

    static VentanaBase* instance; // Instancia única
    Ui::VentanaBase *ui; // Variable ui para acceder a los widgets

    // Métodos para evitar la copia y asignación
    VentanaBase(const VentanaBase&) = delete;
    VentanaBase& operator=(const VentanaBase&) = delete;

    //FUNCIONES Y METODOS
    void initComponents();

};

#endif // VENTANABASE_H
