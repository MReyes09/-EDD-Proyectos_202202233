#ifndef DIALOGNEWPOST_H
#define DIALOGNEWPOST_H

#include <QDialog>

namespace Ui {
class DialogNewPost;
}

class DialogNewPost : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewPost(QWidget *parent = nullptr);
    ~DialogNewPost();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_btn_setImage_clicked();

private:
    QString path = "";
    Ui::DialogNewPost *ui;
    QString getPath();
    void setImage();
};

#endif // DIALOGNEWPOST_H
