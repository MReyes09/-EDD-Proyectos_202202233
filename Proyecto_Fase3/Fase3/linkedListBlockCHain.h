#ifndef LINKEDLISTBLOCKCHAIN_H
#define LINKEDLISTBLOCKCHAIN_H

#include "bloque.h"

#include <QCryptographicHash>  // Para calcular el hash
#include <QDebug>              // Para imprimir en la consola
#include <QJsonObject>         // Para generar el objeto JSON
#include <QJsonDocument>       // Para manejar documentos JSON
#include <QFile>               // Para guardar archivos
#include <QJsonArray>          // Para manejar arreglos JSON

struct NodeBlock{

    Bloque* data;
    NodeBlock *next;

    NodeBlock(Bloque *data_): data(data_), next(nullptr){};

};

class LinkedListBlockChain{

public:
    int indexChain = 0;
    NodeBlock *head;

    LinkedListBlockChain(): head(nullptr){};

    ~LinkedListBlockChain()
    {
        NodeBlock* current = head;
        while(current != nullptr)
        {
            NodeBlock* next = current->next;
            delete current;
            current = next;
        }
    };

    bool AppendBlock(Bloque* nuevoBloque){

        //Agregar informacion al bloque
        nuevoBloque->INDEX = indexChain;
        indexChain++;

        NodeBlock* newNode = new NodeBlock(nuevoBloque);
        if (head == nullptr)
        {
            head = newNode;
            newNode->data->PREVIOUSHASH = "0000";
            newNode->data->HASH = generateHash(indexChain, nuevoBloque->TIMESTAMP, "0000", nuevoBloque->PREVIOUSHASH);
            return true;
        }

        NodeBlock* temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }

        newNode->data->PREVIOUSHASH = temp->data->HASH; // ASIGNO EL PREVIOUSHASH
        newNode->data->HASH = generateHash(indexChain, nuevoBloque->TIMESTAMP, "0000", nuevoBloque->PREVIOUSHASH);
        temp->next = newNode;

        return true;

    };

    QString generateHash(int index, QString timestamp, QString nonce, QString previoushash){

        QString data = QString::number(index) + timestamp + nonce + previoushash;

        //calculo del sha256
        QByteArray hashData = QCryptographicHash::hash(data.toUtf8(), QCryptographicHash::Sha256);
        // Convertir el resultado del hash a una cadena hexadecimal
        QString hashString = hashData.toHex();

        // Agregar el prefijo "0000" al inicio del hash
        QString finalHash = "0000" + hashString;

        return finalHash;
    }

    // Función para imprimir el contenido de cada bloque en la blockchain
    void print() {
        NodeBlock* current = head;
        while (current != nullptr) {
            qDebug() << "Bloque:";
            qDebug() << "INDEX:" << current->data->INDEX;
            qDebug() << "TIMESTAMP:" << current->data->TIMESTAMP;
            qDebug() << "PREVIOUSHASH:" << current->data->PREVIOUSHASH;
            qDebug() << "HASH:" << current->data->HASH;
            qDebug() << "-----------------------------";
            current = current->next;
        }
    }

    void generateJSON() {
        QString fixedPath = "C:/Users/matth/OneDrive/Documentos/Proyectos C++/EDD_Proyectos_202202233/Proyecto_Fase3/Fase3/blockChain/";

        NodeBlock* current = head;
        while (current != nullptr) {
            // Construir manualmente el JSON en el orden deseado
            QString jsonString = QString(
                                     "{\n"
                                     "    \"INDEX\": %1,\n"
                                     "    \"TIMESTAMP\": \"%2\",\n"
                                     "    \"NONCE\": \"%3\",\n"
                                     "    \"DATA\": %4,\n"
                                     "    \"PREVIOUSHASH\": \"%5\",\n"
                                     "    \"HASH\": \"%6\"\n"
                                     "}"
                                     ).arg(current->data->INDEX)
                                     .arg(current->data->TIMESTAMP)
                                     .arg(current->data->NONCE)
                                     .arg(QString(current->data->DATA))
                                     .arg(current->data->PREVIOUSHASH)
                                     .arg(current->data->HASH);

            // Nombre del archivo usando el INDEX del bloque (por ejemplo, "BloqueNo0.json")
            QString filename = "BloqueNo" + QString::number(current->data->INDEX) + ".json";

            // Ruta completa del archivo incluyendo el nombre
            QString fullFilePath = fixedPath + filename;

            // Guardar el JSON en un archivo
            QFile file(fullFilePath);
            if (file.open(QIODevice::WriteOnly)) {
                file.write(jsonString.toUtf8());
                file.close();
                qDebug() << "Archivo JSON guardado:" << filename;
            } else {
                qDebug() << "Error al guardar el archivo JSON:" << filename;
            }

            current = current->next;
        }
    }



};

#endif // LINKEDLISTBLOCKCHAIN_H
