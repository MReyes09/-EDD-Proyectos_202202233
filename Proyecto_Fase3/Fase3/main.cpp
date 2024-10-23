#include <QApplication>
#include "menu.h"
#include "user_controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Menu *menu = new Menu();
    menu->ventanaBase->show();

    // Obtener instancia del User_Controller
    User_Controller *ctrUser = User_Controller::getInstance();

    // Conectar la señal aboutToQuit() de QApplication para generar los JSON justo antes de cerrar
    QObject::connect(&a, &QApplication::aboutToQuit, [ctrUser]() {
        ctrUser->generateJsonBlockChain();
        qDebug() << "Generando JSON antes de cerrar la aplicación...";
    });

    return a.exec();
}
