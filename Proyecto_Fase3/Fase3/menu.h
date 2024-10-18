#ifndef MENU_H
#define MENU_H

#include "ventanabase.h"

class Menu
{
public:
    VentanaBase *ventanaBase;
    Menu();
    ~Menu();
    VentanaBase* getInstanceVentanaBase();

};

#endif // MENU_H
