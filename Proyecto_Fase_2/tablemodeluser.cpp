#include "tablemodeluser.h"


TableModelUser::TableModelUser(QObject *parent) : QAbstractTableModel(parent), usersList(nullptr)
{

}

void TableModelUser::setUsers(LinkedList& users)
{
    usersList = &users;
    usersList->print();
}

// Retorna la cantidad de filas que tiene la tabla
int TableModelUser::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return usersList ? usersList->size_List() : 0;
}

// Retorna la cantidad de columnas que tiene la tabla
int TableModelUser::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    // Asumimos que tenemos 5 columnas (ID, Nombre, Apellido, Correo, Rol)
    return 5;
}

// Retorna los datos que se mostrarán en la celda dada por el índice
QVariant TableModelUser::data(const QModelIndex &index, int role) const
{
    if (!usersList || role != Qt::DisplayRole)
        return QVariant();

    User* user = usersList->at(index.row());  // Obtenemos el usuario en la fila correspondiente
    if (!user)
        return QVariant();

    // Seleccionamos el dato a mostrar en base a la columna
    switch (index.column()) {
    case 0:
        return user->getIdUser();  // Columna 1: ID del usuario
    case 1:
        return user->getName();    // Columna 2: Nombre
    case 2:
        return user->getLastname(); // Columna 3: Apellido
    case 3:
        return user->getEmail();   // Columna 4: Correo
    case 4:
        return user->getRol();     // Columna 5: Rol
    default:
        return QVariant();
    }
}

// Retorna los encabezados de las columnas
QVariant TableModelUser::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("ID");
        case 1:
            return QString("Nombre");
        case 2:
            return QString("Apellido");
        case 3:
            return QString("Correo");
        case 4:
            return QString("Rol");
        default:
            return QVariant();
        }
    }

    return QVariant();
}
