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
    int No_Comentarios;

    // Constructor con pathImage como argumento opcional
    Publicacion(QString email_, QString contenido_, QDate fecha_, QString hora_, int No_Comentarios_ = 0, QString pathImage_ = "")
        : email(email_), contenido(contenido_), fecha(fecha_), hora(hora_), pathImage(pathImage_), No_Comentarios(No_Comentarios_) {}
};

#endif
