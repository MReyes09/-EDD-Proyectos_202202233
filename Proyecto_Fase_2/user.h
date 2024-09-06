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
    User(int id_User_, QString name_, QString lastname_, QString email_, QString password_, QString birthdate_, QString rol_);
};

#endif // USER_H
