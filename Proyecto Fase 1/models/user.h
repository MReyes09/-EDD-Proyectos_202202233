// user.h
#ifndef USER_H
#define USER_H

#include <string>
#include "../data_Structs/LinkedList_Sol.cpp"

using namespace std;

class User {
    private:
        int id_User;
        string name;
        string lastname;
        string email;
        string password;
        string birthdate;
        string rol;
        LinkedList_Sol list_Envios;
        LinkedList_Sol list_Sol;
        LinkedList_Sol amigos;

    public:
        // Constructor
        int No_Post;
        int No_Fri;
        User(int id_User_, string name_, string lastname_, string email_, string password_, string birthdate_, string rol_);

        // Getters
        int getIdUser() const;
        string getName() const;
        string getLastname() const;
        string getEmail() const;
        string getPassword() const;
        string getBirthdate() const;
        string getRol() const;
        LinkedList_Sol& getListEnvios();
        LinkedList_Sol& getListSol();
        LinkedList_Sol& getListAmigos();

        // Setters
        void setIdUser(int id);
        void setName(string name_);
        void setLastname(string lastname_);
        void setEmail(string email_);
        void setPassword(string password_);
        void setBirthdate(string birthdate_);
        void setRol(string rol_);
};

#endif // USER_H
