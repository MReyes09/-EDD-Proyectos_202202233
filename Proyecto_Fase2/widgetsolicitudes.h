#ifndef WIDGETSOLICITUDES_H
#define WIDGETSOLICITUDES_H

#include <QWidget>

namespace Ui {
class WidgetSolicitudes;
}

class WidgetSolicitudes : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetSolicitudes(QWidget *parent = nullptr);
    ~WidgetSolicitudes();

private:
    Ui::WidgetSolicitudes *ui;
    void initComponents();
};

#endif // WIDGETSOLICITUDES_H
