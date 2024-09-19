#ifndef WIDGETBUSCARUSER_H
#define WIDGETBUSCARUSER_H

#include <QWidget>

namespace Ui {
class WidgetBuscarUser;
}

class WidgetBuscarUser : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetBuscarUser(QWidget *parent = nullptr);
    ~WidgetBuscarUser();

private slots:
    void on_pushButton_clicked();

private:
    Ui::WidgetBuscarUser *ui;
};

#endif // WIDGETBUSCARUSER_H
