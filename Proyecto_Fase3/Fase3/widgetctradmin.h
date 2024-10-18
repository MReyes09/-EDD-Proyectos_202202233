#ifndef WIDGETCTRADMIN_H
#define WIDGETCTRADMIN_H

#include <QWidget>

namespace Ui {
class WidgetCtrAdmin;
}

class WidgetCtrAdmin : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetCtrAdmin(QWidget *parent = nullptr);
    ~WidgetCtrAdmin();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::WidgetCtrAdmin *ui;
    void cambiarWidgetAdmin(QWidget* widgetChange);
};

#endif // WIDGETCTRADMIN_H
