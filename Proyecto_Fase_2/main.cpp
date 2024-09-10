#include "mainview.h"
#include "adminvew.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainView login;
    if(login.exec() == QDialog::Rejected){
        return -1;
    }

    AdminVew adminView(login.getTipo());
    adminView.show();

    return a.exec();
}
