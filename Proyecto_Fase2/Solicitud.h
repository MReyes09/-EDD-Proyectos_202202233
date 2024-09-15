#ifndef SOLICITUD_H
#define SOLICITUD_H

#include <QString>

using namespace std;

class Solicitud {

private:
    QString correo_Emisor;
    QString correo_Receptor;

public:
    // Constructor
    Solicitud(QString correoEm, QString correoRec)
        : correo_Emisor(correoEm), correo_Receptor(correoRec) {}

    // Getters
    QString getCorreoEmisor() const {
        return correo_Emisor;
    }

    QString getCorreoReceptor() const {
        return correo_Receptor;
    }

    // Setters
    void setCorreoEmisor(const QString& correoEm) {
        correo_Emisor = correoEm;
    }

    void setCorreoReceptor(const QString& correoRec) {
        correo_Receptor = correoRec;
    }
};

#endif
