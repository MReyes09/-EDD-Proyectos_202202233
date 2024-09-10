#ifndef TABLEMODELUSER_H
#define TABLEMODELUSER_H

#include <QObject>
#include <QAbstractTableModel>
#include "linkedlist.h"

class TableModelUser : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TableModelUser(QObject *parent = nullptr);
    // Método para establecer los datos
    void setUsers(LinkedList &users);

    // Implementar los métodos del modelo
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    LinkedList* usersList;  // Lista enlazada de usuarios

};

#endif // TABLEMODELUSER_H
