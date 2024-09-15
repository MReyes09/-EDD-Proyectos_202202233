#ifndef VIEWSCTR_H
#define VIEWSCTR_H

//Ventana Principal y unica
#include "ventanabase.h"

//Widgets que sirven de plantilla para el widgetBase de Principal
#include "widget_sigup.h"
#include "widget_login.h"
#include "widgetctradmin.h"
#include "widget_ctruser_admin.h"
#include "widgetcargasmasivas.h"
#include "widgetreports.h"
#include "dialog_reporte.h"
#include "widgetctruser.h"
#include "widgetperfil.h"
#include "widgetpublicaciones.h"

class ViewsCtr
{
public:
    /*
        Esta clase me brinda a mi el control de todos los Widgets, para poder
        controlar las instancias y hacer el cambio en la ventana Base, para
        tener un mayor control sobre mi programa
    */
    ViewsCtr();
    VentanaBase* getInstanceVentanaBase();
    Widget_SigUp* getInstanceWidgetSigUp();
    Widget_Login* getInstanceWidgetLogin();
    WidgetCtrAdmin* getIntanceWidgetCtrAdmin();
    Widget_CtrUser_Admin* getInstanceWidget_CtrUser_Admin();
    WidgetCargasMasivas* getInstanceWidgetCargasMasivas();
    WidgetReports* getInstanceWidgetReports();
    Dialog_Reporte* getInstanceDialogReporte();

    //USER
    WidgetctrUser* getInstanceWidgetctrUser();
    WidgetPerfil* getInstanceWidgetPerfil();
    WidgetPublicaciones* getInstanceWidgetPost();
};

#endif // VIEWSCTR_H
