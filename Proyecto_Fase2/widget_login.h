#ifndef WIDGET_LOGIN_H
#define WIDGET_LOGIN_H

#include <QWidget>

namespace Ui {
class Widget_Login;
}

class Widget_Login : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_Login(QWidget *parent = nullptr);
    ~Widget_Login();

private slots:
    void on_btn_Sigin_clicked();

    void on_btn_Login_clicked();

private:
    Ui::Widget_Login *ui;
};

#endif // WIDGET_LOGIN_H
