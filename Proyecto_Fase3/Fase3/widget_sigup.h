#ifndef WIDGET_SIGUP_H
#define WIDGET_SIGUP_H

#include <QWidget>

namespace Ui {
class Widget_SigUp;
}

class Widget_SigUp : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_SigUp(QWidget *parent = nullptr);
    ~Widget_SigUp();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Widget_SigUp *ui;
};

#endif // WIDGET_SIGUP_H
