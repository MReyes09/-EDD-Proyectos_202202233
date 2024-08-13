// user.cpp
#include "user.h"

// Constructor
User::User(int id_User_, string name_, string lastname_, string email_, string password_, string birthdate_) {
    id_User = id_User_;
    name = name_;
    lastname = lastname_;
    email = email_;
    password = password_;
    birthdate = birthdate_;
}
// Getters
int User::getIdUser() const { return id_User; }
string User::getName() const { return name; }
string User::getLastname() const { return lastname; }
string User::getEmail() const { return email; }
string User::getPassword() const { return password; }
string User::getBirthdate() const { return birthdate; }

// Setters
void User::setIdUser(int id) { id_User = id; }
void User::setName(string name_) { name = name_; }
void User::setLastname(string lastname_) { lastname = lastname_; }
void User::setEmail(string email_) { email = email_; }
void User::setPassword(string password_) { password = password_; }
void User::setBirthdate(string birthdate_) { birthdate = birthdate_; }
