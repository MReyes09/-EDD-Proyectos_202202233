#ifndef SOLICITUD_H
#define SOLICITUD_H

#include <string>

using namespace std;

class Solicitud {

    private:
        string correo_Emisor;
        string correo_Receptor;

    public:
        // Constructor
        Solicitud(string correoEm, string correoRec) 
            : correo_Emisor(correoEm), correo_Receptor(correoRec) {}

        // Getters
        string getCorreoEmisor() const {
            return correo_Emisor;
        }

        string getCorreoReceptor() const {
            return correo_Receptor;
        }

        // Setters
        void setCorreoEmisor(const string& correoEm) {
            correo_Emisor = correoEm;
        }

        void setCorreoReceptor(const string& correoRec) {
            correo_Receptor = correoRec;
        }
};

#endif
