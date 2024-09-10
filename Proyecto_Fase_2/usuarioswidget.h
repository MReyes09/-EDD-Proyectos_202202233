#ifndef USUARIOSWIDGET_H
#define USUARIOSWIDGET_H

#include <QWidget>
#include "user_controller.h"

namespace Ui {
class UsuariosWidget;
}

class UsuariosWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UsuariosWidget(QWidget *parent = nullptr);
    ~UsuariosWidget();

private:
    Ui::UsuariosWidget *ui;
    User_Controller* ctrUser;
};

#endif // USUARIOSWIDGET_H
