#ifndef WIDGETCARGASMASIVAS_H
#define WIDGETCARGASMASIVAS_H

#include <QWidget>

namespace Ui {
class WidgetCargasMasivas;
}

class WidgetCargasMasivas : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetCargasMasivas(QWidget *parent = nullptr);
    ~WidgetCargasMasivas();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::WidgetCargasMasivas *ui;
    QString get_Path();
};

#endif // WIDGETCARGASMASIVAS_H
