#include "viewsctr.h"
#include <QWidget>

ViewsCtr::ViewsCtr() {}

VentanaBase* ViewsCtr::getInstanceVentanaBase(){
    return VentanaBase::getInstance();
}


Widget_SigUp* ViewsCtr::getInstanceWidgetSigUp(){
    return new Widget_SigUp();
}

Widget_Login* ViewsCtr::getInstanceWidgetLogin(){
    return new Widget_Login();
}

WidgetCtrAdmin* ViewsCtr::getIntanceWidgetCtrAdmin()
{
    return new WidgetCtrAdmin();
}

Widget_CtrUser_Admin* ViewsCtr::getInstanceWidget_CtrUser_Admin()
{
    return new Widget_CtrUser_Admin();
}

WidgetCargasMasivas* ViewsCtr::getInstanceWidgetCargasMasivas()
{
    return new WidgetCargasMasivas();
}

WidgetReports* ViewsCtr::getInstanceWidgetReports()
{
    return new WidgetReports();
}

Dialog_Reporte* ViewsCtr::getInstanceDialogReporte()
{
    return new Dialog_Reporte();
}

//USERS

WidgetctrUser* ViewsCtr::getInstanceWidgetctrUser()
{
    return new WidgetctrUser();
}

WidgetPerfil* ViewsCtr::getInstanceWidgetPerfil()
{
    return new WidgetPerfil();
}

WidgetPublicaciones* ViewsCtr::getInstanceWidgetPost()
{
    return new WidgetPublicaciones();
}

