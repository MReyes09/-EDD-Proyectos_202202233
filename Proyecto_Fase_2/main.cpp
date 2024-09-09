#include "mainview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainView w;
    w.show();
    return a.exec();
}
