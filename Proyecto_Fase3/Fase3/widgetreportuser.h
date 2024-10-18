#ifndef WIDGETREPORTUSER_H
#define WIDGETREPORTUSER_H

#include "NodePost.h"

#include <QWidget>

namespace Ui {
class widgetReportUser;
}

class widgetReportUser : public QWidget
{
    Q_OBJECT

public:
    explicit widgetReportUser(QWidget *parent = nullptr);
    ~widgetReportUser();

private slots:
    void on_pushButton_clicked();

private:
    NodePost *head;
    Ui::widgetReportUser *ui;
    void initComponents();
};

#endif // WIDGETREPORTUSER_H
