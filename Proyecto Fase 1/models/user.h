// user.h
#ifndef USER_H
#define USER_H

#include <string>

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

    public:
        // Constructor
        User(int id_User_, string name_, string lastname_, string email_, string password_, string birthdate_, string rol_);

        // Getters
        int getIdUser() const;
        string getName() const;
        string getLastname() const;
        string getEmail() const;
        string getPassword() const;
        string getBirthdate() const;
        string getRol() const;

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
