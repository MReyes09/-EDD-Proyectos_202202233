#ifndef PUBLICACION_H
#define PUBLICACION_H

#include <string>

using namespace std;

class Publicacion {

    public:

        string email;
        string contenido;
        string fecha;
        string hora;

        Publicacion(string email_, string contenido_, string fecha_, string hora_)
            : email(email_), contenido(contenido_), fecha(fecha_), hora(hora_) {}

};

#endif