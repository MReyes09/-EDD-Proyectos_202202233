#ifndef WIDGET_CTRUSER_ADMIN_H
#define WIDGET_CTRUSER_ADMIN_H

#include "linkedlist.h"
#include <QWidget>

namespace Ui {
class Widget_CtrUser_Admin;
}

class Widget_CtrUser_Admin : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_CtrUser_Admin(QWidget *parent = nullptr);
    ~Widget_CtrUser_Admin();

private slots:
    void on_pushButton_clicked();

    void on_btn_Aplicar_clicked();

private:
    Ui::Widget_CtrUser_Admin *ui;
    void initComponents();
    void appendTable(LinkedList* list);
};

#endif // WIDGET_CTRUSER_ADMIN_H
