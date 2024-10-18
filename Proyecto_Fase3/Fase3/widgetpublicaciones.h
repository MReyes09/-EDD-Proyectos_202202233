#ifndef WIDGETPUBLICACIONES_H
#define WIDGETPUBLICACIONES_H

#include <QWidget>
#include "NodePost.h"

namespace Ui {
class WidgetPublicaciones;
}

class WidgetPublicaciones : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetPublicaciones(QWidget *parent = nullptr);
    ~WidgetPublicaciones();

private slots:
    void on_btn_siguiente_clicked();

    void on_btn_ApliDate_clicked();

    void on_btn_CrearPost_clicked();

    void on_btnAplicarOrden_clicked();

private:
    NodePost *head;
    Ui::WidgetPublicaciones *ui;
    void initialComponents();
};

#endif // WIDGETPUBLICACIONES_H
