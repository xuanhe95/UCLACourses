
#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include <string>
#include "treemm.h"
#include <iostream>
#include <vector>

class User;

class UserDatabase
{
  public:
    UserDatabase();
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;
    ~UserDatabase();
    
    //debug
    std::vector <User*> get_users() {
        return m_users;
    }
    
    TreeMultimap <std::string, User*> get_userMap(){
        return m_userMap;
    }
    
    TreeMultimap<std::string, User*>::Iterator get_userMap_it (const std::string& email) const {
        return m_userMap.find(email);
    }
    
  private:
    TreeMultimap <std::string, User*> m_userMap;
    std::vector <User*> m_users;
};

#endif // USERDATABASE_INCLUDED

