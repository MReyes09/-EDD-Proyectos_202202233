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

private:
    Ui::WidgetPerfil *ui;
};

#endif // WIDGETPERFIL_H
