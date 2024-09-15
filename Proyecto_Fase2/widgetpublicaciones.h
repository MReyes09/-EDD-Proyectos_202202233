#ifndef WIDGETPUBLICACIONES_H
#define WIDGETPUBLICACIONES_H

#include <QWidget>

namespace Ui {
class WidgetPublicaciones;
}

class WidgetPublicaciones : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetPublicaciones(QWidget *parent = nullptr);
    ~WidgetPublicaciones();

private:
    Ui::WidgetPublicaciones *ui;
};

#endif // WIDGETPUBLICACIONES_H
