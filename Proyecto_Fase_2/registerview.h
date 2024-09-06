#ifndef REGISTERVIEW_H
#define REGISTERVIEW_H

#include <QDialog>

namespace Ui {
class registerView;
}

class registerView : public QDialog
{
    Q_OBJECT

public:
    explicit registerView(QWidget *parent = nullptr);
    ~registerView();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::registerView *ui;
};

#endif // REGISTERVIEW_H
