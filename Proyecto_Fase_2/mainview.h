#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QDialog>
#include "registerview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class mainView;
}
QT_END_NAMESPACE

class mainView : public QDialog
{
    Q_OBJECT

public:
    enum Tipo
    {
        USUARIO, ADMIN
    };

    explicit mainView(QWidget *parent = nullptr);
    ~mainView();
    int getTipo() const { return tipo; }

private slots:
    void on_btn_Login_clicked();
    void on_btn_Sigin_clicked();

private:
    Ui::mainView *ui;
    registerView *regView;
    int tipo;

};

#endif // MAINVIEW_H
