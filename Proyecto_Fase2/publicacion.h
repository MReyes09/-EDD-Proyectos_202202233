#ifndef PUBLICACION_H
#define PUBLICACION_H

#include <QString>
#include <QDate>

using namespace std;

class Publicacion {

public:
    QString email;
    QString contenido;
    QDate fecha;
    QString hora;
    QString pathImage;  // Nuevo atributo para almacenar la ruta de la imagen

    // Constructor con pathImage como argumento opcional
    Publicacion(QString email_, QString contenido_, QDate fecha_, QString hora_, QString pathImage_ = "")
        : email(email_), contenido(contenido_), fecha(fecha_), hora(hora_), pathImage(pathImage_) {}
};

#endif
