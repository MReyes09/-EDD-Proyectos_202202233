#ifndef USER_H
#define USER_H

#include <QString>

using namespace std;

class User
{
private:
    int id_User;
    QString name;
    QString lastname;
    QString email;
    QString password;
    QString birthdate;
    QString rol;
    //LinkedList_Sol list_Envios;
    //LinkedList_Sol list_Sol;
    //LinkedList_Sol amigos;

public:
    int No_Post;
    int No_Fri;
    //Constructor
    User(int id_User_, QString name_, QString lastname_, QString email_, QString password_, QString birthdate_, QString rol_);

    // Setters
    void setIdUser(int id);
    void setName(QString name_);
    void setLastname(QString lastname_);
    void setEmail(QString email_);
    void setPassword(QString password_);
    void setBirthdate(QString birthdate_);
    void setRol(QString rol_);

    //Getters
    int getIdUser() const;
    QString getName() const;
    QString getLastname() const;
    QString getEmail() const;
    QString getPassword() const;
    QString getBirthdate() const;
    QString getRol() const;
};

#endif // USER_H
