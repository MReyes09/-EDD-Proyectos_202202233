#ifndef WIDGETCTRUSER_H
#define WIDGETCTRUSER_H

#include <QWidget>

namespace Ui {
class WidgetctrUser;
}

class WidgetctrUser : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetctrUser(QWidget *parent = nullptr);
    ~WidgetctrUser();

private slots:
    void on_btnCerrarSesion_clicked();
    void on_btn_Perfil_clicked();
    void cambiarWidget(QWidget* widgetChange);

    void on_btn_WPost_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::WidgetctrUser *ui;
};

#endif // WIDGETCTRUSER_H
