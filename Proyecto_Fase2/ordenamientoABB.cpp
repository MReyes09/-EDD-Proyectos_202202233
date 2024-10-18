
#include <QDate>

using namespace std;

// Estructura para almacenar fecha y cantidad de publicaciones
struct FechaPublicacion {
    QDate fecha;
    int cantidad;

    // Constructor
    FechaPublicacion(QDate f, int c) : fecha(f), cantidad(c) {}
};
