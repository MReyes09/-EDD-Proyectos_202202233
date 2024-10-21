#ifndef WIDGETPERFIL_H
#define WIDGETPERFIL_H

#include <QWidget>

namespace Ui {
class WidgetPerfil;
}

class WidgetPerfil : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetPerfil(QWidget *parent = nullptr);
    ~WidgetPerfil();

private slots:
    void on_btn_UpdateData_clicked();

private:
    Ui::WidgetPerfil *ui;
    void initComponents();
};

#endif // WIDGETPERFIL_H
