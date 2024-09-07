#include "user.h"
#include <QString>

User::User(int id_User_, QString name_, QString lastname_, QString email_, QString password_, QString birthdate_, QString rol_) {
    id_User = id_User_;
    name = name_;
    lastname = lastname_;
    email = email_;
    password = password_;
    birthdate = birthdate_;
    rol = rol_;
    No_Post = 0;
    No_Fri = 0;
}

// Getters
int User::getIdUser() const { return id_User; }
QString User::getName() const { return name; }
QString User::getLastname() const { return lastname; }
QString User::getEmail() const { return email; }
QString User::getPassword() const { return password; }
QString User::getBirthdate() const { return birthdate; }
QString User::getRol() const { return rol; }
//LinkedList_Sol& User::getListEnvios() { return list_Envios; }
//LinkedList_Sol& User::getListSol() { return list_Sol; }
//LinkedList_Sol& User::getListAmigos() { return amigos; }

// Setters
void User::setIdUser(int id) { id_User = id; }
void User::setName(QString name_) { name = name_; }
void User::setLastname(QString lastname_) { lastname = lastname_; }
void User::setEmail(QString email_) { email = email_; }
void User::setPassword(QString password_) { password = password_; }
void User::setBirthdate(QString birthdate_) { birthdate = birthdate_; }
void User::setRol(QString rol_) { rol = rol_; }

