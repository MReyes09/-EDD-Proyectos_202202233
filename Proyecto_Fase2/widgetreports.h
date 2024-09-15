#ifndef WIDGETREPORTS_H
#define WIDGETREPORTS_H

#include <QWidget>

namespace Ui {
class WidgetReports;
}

class WidgetReports : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetReports(QWidget *parent = nullptr);
    ~WidgetReports();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::WidgetReports *ui;
};

#endif // WIDGETREPORTS_H
