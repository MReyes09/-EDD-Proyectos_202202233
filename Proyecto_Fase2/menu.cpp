#include "menu.h"

Menu::Menu() : ventanaBase(VentanaBase::getInstance())
{
}

VentanaBase* Menu::getInstanceVentanaBase()
{
    return ventanaBase;
}
