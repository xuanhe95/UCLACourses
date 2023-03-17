
#include "UserDatabase.h"
#include "User.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

UserDatabase::UserDatabase(){}

UserDatabase::~UserDatabase(){
//use m_users to keep track of the memories and delete the new users created
  for (vector<User*>::iterator it = m_users.begin(); it !=  m_users.end();){
        delete *it;
      *it = nullptr;
        it = m_users.erase(it);
    }
}

bool UserDatabase::load(const string& filename)
{
    //load the file
    ifstream users(filename);
    if (!users) {
        return false;
    }

    string line, name, email, movie, count;
    int num;
    vector<string> watch_history;
    
    //loop to extract information
    while (getline(users, name)) {
        getline(users, email);
        getline(users, count);
        num = stoi(count);      //convert string to int
        while (watch_history.size() < num) {
            std::getline(users, movie);
            watch_history.push_back(movie);
        }
        User* user = new User(name, email, watch_history);
        m_users.push_back(user);        //push the new user into the vector to keep track of memory
        m_userMap.insert(email, user);
        
        watch_history.clear();  //clear watch_history for the next loop
        if (!getline(users, line)){
            break;      //there may or may not be a blank line at last
        }
    }
    return true;
        
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    return m_userMap.find(email).get_value();
}
