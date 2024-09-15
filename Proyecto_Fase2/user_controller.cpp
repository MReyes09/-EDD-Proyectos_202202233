#include "user_controller.h"
#include "publicacion.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QDebug>
#include <QDate>

using namespace std;

// Inicializar el puntero a la instancia como nullptr
User_Controller* User_Controller::instance = nullptr;

// Constructor privado (no se puede instanciar fuera de la clase)
User_Controller::User_Controller()
{
    id_User = 0;
    admin_add();
}

// Método para obtener la instancia única de la clase
User_Controller* User_Controller::getInstance() {
    if (instance == nullptr) {
        instance = new User_Controller();
    }
    return instance;
}

bool User_Controller::sigIn(QString name_, QString lastname_, QString email_, QString password_, QString birthdate_, QString rol_)
{
    User* newUser = new User(id_User, name_, lastname_, email_, password_, birthdate_, "User");
    id_User += 1;
    return list_Users.append(newUser);
}

void User_Controller::admin_add()
{
    QString name = "admin@gmail.com";
    QString password = "EDD2S2024";

    User *newUser = new User(id_User, name, "", name, password, "", "Admin");
    id_User += 1;
    list_Users.append(newUser);

}

User* User_Controller::logIn(QString gmail, QString password)
{

    User_Logued = list_Users.search_LogIn(gmail, password);
    if( User_Logued == nullptr )
    {
        return nullptr;
    }
    else
    {
        return User_Logued;
    }

}

User* User_Controller::addUserTable(int index)
{
    return list_Users.at(index);
}

int User_Controller::sizeList()
{
    return list_Users.size_List();
}

LinkedList& User_Controller::getListaUsers()
{
    return list_Users;
}

bool User_Controller::carga_Usuarios(QString path){

    QFile file(path);

    // Verificar si se puede abrir el archivo
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "No se pudo abrir el archivo";
        return false;
    }

    // Leer todo el contenido del archivo
    QByteArray fileData = file.readAll();
    file.close();

    // Parsear el contenido como JSON
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData, &jsonError);

    // Verificar si hubo un error al parsear el JSON
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << "Error al parsear JSON:" << jsonError.errorString();
        return false;
    }

    // Verificar que el documento sea un array de JSON
    if (!jsonDoc.isArray()) {
        qDebug() << "El archivo JSON no contiene un array de usuarios";
        return false;
    }

    // Obtener el array de usuarios
    QJsonArray jsonArray = jsonDoc.array();

    // Iterar sobre los elementos del JSON y crear objetos User
    for (const QJsonValue& value : jsonArray) {
        if (value.isObject()) {
            QJsonObject obj = value.toObject();
            QString name = obj["nombres"].toString();
            QString lastname = obj["apellidos"].toString();
            QString birthdate = obj["fecha_De_Nacimiento"].toString();
            QString email = obj["correo"].toString();
            QString password = obj["contraseña"].toString();
            QString rol = "Usuario";  // Podrías agregar esto a tu JSON si es necesario

            // Crear y agregar el nuevo usuario
            User* newUser = new User(id_User, name, lastname, email, password, birthdate, rol);
            id_User++;
            list_Users.append(newUser, 1);
        }
    }

    return true;
}

bool User_Controller::carga_Solicitudes(QString path)
{
    QFile solicitudesFile(path);

    // Verificar si se puede abrir el archivo
    if (!solicitudesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "No se pudo abrir el archivo";
        return false;
    }

    // Leer todo el contenido del archivo
    QByteArray fileData = solicitudesFile.readAll();
    solicitudesFile.close();

    // Parsear el contenido como JSON
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData, &jsonError);

    // Verificar si hubo un error al parsear el JSON
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << "Error al parsear JSON:" << jsonError.errorString();
        return false;
    }

    // Verificar que el documento sea un array de JSON
    if (!jsonDoc.isArray()) {
        qDebug() << "El archivo JSON no contiene un array de solicitudes";
        return false;
    }

    // Obtener el array de solicitudes
    QJsonArray jsonArray = jsonDoc.array();

    // Iterar sobre los elementos del JSON y procesar solicitudes
    for (const QJsonValue& value : jsonArray) {
        if (value.isObject()) {
            QJsonObject obj = value.toObject();
            QString emisor = obj["emisor"].toString();
            QString receptor = obj["receptor"].toString();
            QString estado = obj["estado"].toString();

            User* userEM = list_Users.search_By_Id(-1, emisor);
            User* userRec = list_Users.search_By_Id(-1, receptor);

            if (userEM != nullptr && userRec != nullptr) {
                Solicitud* newSolicitud = new Solicitud(emisor, receptor);

                if (estado == "PENDIENTE") {
                    // Verificar si ya existe la solicitud
                    if (userEM->getListEnvios().search(userRec->getEmail(), userEM->getEmail())) {
                        qDebug() << "La solicitud entre " << emisor << " y " << receptor << " ya existe";
                        delete newSolicitud;
                        continue;
                    }
                    if (userEM->getListAmigos().search(userRec->getEmail(), userEM->getEmail())) {
                        qDebug() << "Entre " << emisor << " y " << receptor << " ya existe una amistad";
                        delete newSolicitud;
                        continue;
                    }

                    // Agregar solicitud a envíos del emisor y solicitudes del receptor
                    userEM->getListEnvios().append(newSolicitud, userEM->getEmail());
                    userRec->getListSol().push(newSolicitud);
                } else {
                    // Estado aceptado, agregar a la lista de amigos y a la matriz
                    userEM->getListAmigos().append(newSolicitud, userEM->getEmail());
                    userRec->getListAmigos().append(newSolicitud, userRec->getEmail());

                    userEM->No_Fri += 1;
                    userRec->No_Fri += 1;

                    int i = userEM->getIdUser();
                    int j = userRec->getIdUser();

                    add_Matriz(newSolicitud, i, j);
                }
            } else {
                if (userEM == nullptr) {
                    qDebug() << "El usuario con correo: " << emisor << " no existe";
                }
                if (userRec == nullptr) {
                    qDebug() << "El usuario con correo: " << receptor << " no existe";
                }
            }
        }
    }
    return true;
}

void User_Controller::add_Matriz(Solicitud* solicitud, int i, int j)
{
    m.insert(i, j, solicitud);
    m.insert(j,i, solicitud);
    //m.print();
    //cout << "\n" << endl;
}

bool User_Controller::carga_Post(QString path)
{
    QFile publicacionesFile(path);

    // Verificar si se puede abrir el archivo
    if (!publicacionesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "No se pudo abrir el archivo";
        return false;
    }

    // Leer todo el contenido del archivo
    QByteArray fileData = publicacionesFile.readAll();
    publicacionesFile.close();

    // Parsear el contenido como JSON
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData, &jsonError);

    // Verificar si hubo un error al parsear el JSON
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << "Error al parsear JSON:" << jsonError.errorString();
        return false;
    }

    // Verificar que el documento sea un array de JSON
    if (!jsonDoc.isArray()) {
        qDebug() << "El archivo JSON no contiene un array de solicitudes";
        return false;
    }

    // Obtener el array de solicitudes
    QJsonArray jsonArray = jsonDoc.array();

    // Iterar sobre los elementos del JSON y crear objetos User
    for (const QJsonValue& value : jsonArray) {
        if (value.isObject()) {
            QJsonObject obj = value.toObject();
            QString correo = obj["correo"].toString();
            QString contenido = obj["contenido"].toString();
            QString fechaStr = obj["fecha"].toString();
            QString hora = obj["hora"].toString();

            QDate fecha = QDate::fromString(fechaStr, "dd/MM/yyyy");

            User* findUser = list_Users.search_By_Id(-1, correo);
            findUser->No_Post += 1;
            // Crear y agregar la nueva publicacion
            Publicacion* newPost = new Publicacion(correo, contenido, fecha, hora);
            posts.append(newPost);
            //list_Users.append(newUser, 1);
        }
    }

    return true;

}

void User_Controller::report_Posts(){
    posts.graph();
    posts.generateDot();
}

ABB* User_Controller::arbolAbb(){

}

