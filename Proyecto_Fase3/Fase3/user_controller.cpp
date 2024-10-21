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
    allPosts = nullptr;
    arbolBBusqueda = nullptr;
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
    return list_Users.append(newUser, -1);
}

void User_Controller::admin_add()
{
    QString name = "admin@gmail.com";
    QString password = "EDD2S2024";

    User *newUser = new User(id_User, name, "", name, password, "", "Admin");
    id_User += 1;
    list_Users.append(newUser, -1);

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

AVL& User_Controller::getListaUsers()
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
            QString birthdate = obj["fecha_de_nacimiento"].toString();
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
                        QMessageBox::information(nullptr, "Estado de solicitud", "La solicitud entre " + emisor + " y " + receptor + " ya existe");
                        delete newSolicitud;
                        continue;
                    }
                    if (userEM->getListAmigos().search(userRec->getEmail(), userEM->getEmail())) {
                        QMessageBox::information(nullptr, "Estado de solicitud", "La solicitud entre " + emisor + " y " + receptor + " ya existe");
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

                    add_ListOfList(i, j);
                }
            } else {
                if (userEM == nullptr) {
                    QMessageBox::information(nullptr, "Estado de solicitud", "El usuario con correo: " + emisor + " no existe");
                }
                if (userRec == nullptr) {
                    QMessageBox::information(nullptr, "Estado de solicitud", "El usuario con correo: " + receptor + " no existe");
                }
            }
        }
    }
    return true;
}

void User_Controller::add_ListOfList(int i, int j)
{
    listOflist.insert(i, j);
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

            // Verificar si la publicación tiene comentarios
            int No_Comentarios = 0;
            if (obj.contains("comentarios") && obj["comentarios"].isArray()) {
                QJsonArray comentariosArray = obj["comentarios"].toArray();
                No_Comentarios = comentariosArray.size();  // Contar los comentarios
            }

            User* findUser = list_Users.search_By_Id(-1, correo);
            findUser->No_Post += 1;
            // Crear y agregar la nueva publicacion
            Publicacion* newPost = new Publicacion(correo, contenido, fecha, hora, No_Comentarios);
            posts.append(newPost);
        }
    }

    return true;

}

void User_Controller::report_Posts(){
    posts.graph();
    posts.generateDot();
}

void User_Controller::arbolAbb(){
    arbolBBusqueda = posts.extractPost(User_Logued->getListAmigos(), User_Logued->getEmail());
}

void User_Controller::allList(){
    allPosts = posts.extractPostAll(User_Logued->getListAmigos(), User_Logued->getEmail());
}

void User_Controller::searchDateAbb(QDate date){

    allPosts = arbolBBusqueda->search(date);

}

void User_Controller::addPost(QString contenido, QString path) {
    QString email =User_Logued->getEmail();

    // Obtener la fecha y hora actual usando QDateTime
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // Formatear la fecha como dd/MM/yyyy
    QDate fecha = currentDateTime.date();

    // Formatear la hora como HH:mm en formato 24 horas
    QString hora = currentDateTime.toString("HH:mm");

    // Crear la nueva publicación
    Publicacion* newPost = new Publicacion(email, contenido, fecha, hora, 0, path);
    posts.append(newPost);
    User_Logued->No_Post += 1;

    arbolAbb();
    allList();
}

User* User_Controller::searchUser(QString correo){
    return list_Users.search_By_Id(-1, correo);
}

AVL* User_Controller::getListaNoAmigos(){
    return list_No_Amigos;
}

void User_Controller::listDesconocidos(){
    list_No_Amigos = list_Users.getDesconocidos(User_Logued->getIdUser(), User_Logued->getListEnvios(), User_Logued->getListSol(), User_Logued->getListAmigos());
};

void User_Controller::solicitudes(int opcion){

    if( opcion == 1 ){ // Esta opcion es cuando el usuario acepta una solicitud

        Solicitud *solicitud = User_Logued->getListSol().head->solicitud;

        bool result = User_Logued->getListSol().remove(solicitud);
        if(result){
            QMessageBox::information(nullptr,"Estado solicitud", "Se acepto con exito la solicitud");
        }else{
            QMessageBox::information(nullptr,"Estado solicitud", "A ocurrido un error, nunca se encontro la solicitud ");
        }

        User* user_Emisor = list_Users.search_By_Id(-1, solicitud->getCorreoEmisor());
        result = user_Emisor->getListEnvios().remove(solicitud);

        if( !result ) {
            QMessageBox::information(nullptr,"Estado solicitud", "A ocurrido un error, nunca se encontro la solicitud ");
        }
        User_Logued->getListAmigos().append_Friend(solicitud);
        User_Logued->No_Fri += 1;
        user_Emisor->getListAmigos().append_Friend(solicitud);
        user_Emisor->No_Fri += 1;
        User_Logued->getListAmigos().print(2, User_Logued->getEmail());
        int i = User_Logued->getIdUser();
        int j = user_Emisor->getIdUser();
        add_ListOfList(i, j);

    }else{  // Esta opcion es cuando el usuario rechaza una solicitud

        Solicitud *solicitud = User_Logued->getListSol().head->solicitud;

        bool result = User_Logued->getListSol().remove(solicitud);
        if(result){
            QMessageBox::information(nullptr,"Estado solicitud", "Se rechazo con exito la solicitud");
        }else{

            QMessageBox::information(nullptr,"Estado solicitud", "A ocurrido un error, nunca se encontro la solicitud ");
        }

        User* user_Emisor =  list_Users.search_By_Id(-1, solicitud->getCorreoEmisor());
        result = user_Emisor->getListEnvios().remove(solicitud);

        if( !result ) {
            QMessageBox::information(nullptr,"Estado solicitud", "A ocurrido un error, nunca se encontro la solicitud ");
        }

        delete solicitud;

    }

}

void User_Controller::cancelarSolicitud(QString email_Sol)
{
    Solicitud* solicitud = User_Logued->getListEnvios().search_Find(email_Sol, User_Logued->getEmail());

    if(solicitud != nullptr)
    {
        bool result = false;
        result = User_Logued->getListEnvios().remove(solicitud);
        User* user_Receptor = list_Users.search_By_Id(-1, solicitud->getCorreoReceptor());
        result = user_Receptor->getListSol().remove(solicitud);
        if(result){
            QMessageBox::information(nullptr,"Estado solicitud", "Se rechazo con exito la solicitud");
            return;
        }else{

            QMessageBox::information(nullptr,"Estado solicitud", "A ocurrido un error, nunca se encontro la solicitud ");
            return;
        }
    }

    QMessageBox::information(nullptr, "Estado de solicitud", "Error en la busqueda de la solicitud");
}

void User_Controller::solicitud_Amistad(QString email) {

    User* user_Solicitud = list_Users.search_By_Id(-1, email);

    if (user_Solicitud != nullptr) {
        Solicitud* newSolicitud = new Solicitud(User_Logued->getEmail(), user_Solicitud->getEmail());
        bool res = User_Logued->getListEnvios().append(newSolicitud, User_Logued->getEmail());
        if( res ){
            user_Solicitud->getListSol().push(newSolicitud);
            QMessageBox::information(nullptr,"Estado solicitud", "Se envio con exito la solicitud");
        }
    } else {
        QMessageBox::information(nullptr, "Estado de solicitud", "Error en el envio de la solicitud");
    }
}

void User_Controller::report_AVL(){
    list_Users.graph();
}

void User_Controller::avl_inorden(LinkedList* listOrden){
    list_Users.inOrderRec(list_Users.root, listOrden);
}

void User_Controller::avl_preorden(LinkedList* listOrden){
    list_Users.preOrder(list_Users.root, listOrden);
}

void User_Controller::avl_posorden(LinkedList* listOrden){
    list_Users.postOrder(list_Users.root, listOrden);
}

LinkedListPost* User_Controller::inordenPosts(int limit){
    return arbolBBusqueda->inOrder(limit);
}

LinkedListPost* User_Controller::posordenPosts(int limit){
    return arbolBBusqueda->postOrder(limit);
}

LinkedListPost* User_Controller::preordenPosts(int limit){
    return arbolBBusqueda->preOrder(limit);
}

void User_Controller::ListOfListGraph(){
    listOflist.graph(list_Users);
}

void User_Controller::ListOfListGraphAsAdjacenty(){
    listOflist.graphAsAdjacencyList(list_Users);
}

void User_Controller::ActualizarUser(QString name, QString lastname, QString birthDay, QString pass){
    User_Logued->setBirthdate(birthDay);
    User_Logued->setLastname(lastname);
    User_Logued->setPassword(pass);
    User_Logued->setName(name);

    QMessageBox::information(nullptr, "Actualización de datos", "Los datos se han actualizado correctamente");

}
