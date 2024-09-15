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

    Publicacion(QString email_, QString contenido_, QDate fecha_, QString hora_)
        : email(email_), contenido(contenido_), fecha(fecha_), hora(hora_) {}

};

#endif
