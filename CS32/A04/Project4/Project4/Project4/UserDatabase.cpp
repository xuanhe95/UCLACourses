#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

UserDatabase::UserDatabase()
{
}

UserDatabase::~UserDatabase() {
    vector<User*>::iterator iter = m_users.begin();
    while (iter != m_users.end()) {
        User* user = *iter;
        iter = m_users.erase(iter);
        delete user;
    }
}

bool UserDatabase::load(const string& filename)
{
    ifstream data(filename);
    if (!data.is_open()) return false;

    string line;
    string name;
    string email;
    string moive;
    string count;
    
    int num = 0;
    while(getline(data, name)){
        //cout << "name: " << name << endl;
        getline(data, email);
        //cout << "email: " << email << endl;
        getline(data, count);
        //cout << "count: " << count << endl;
        vector<string> history;
        while(history.size() < stoi(count)) {
            getline(data, moive);
            //cout << "movies: " << moive << endl;
            history.push_back(moive);
        }
        User* user = new User(name, email, history);

        //cout << num << endl;
        //num++;
        m_users.push_back(user);
        m_map.insert(email, user);
        //getline(data, line);
        if (!getline(data, line)) {
            break;      //there may or may not be a blank line at last
        }
    }
    return true;
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    TreeMultimap<std::string, User*>::Iterator iter = m_map.find(email);

    if (iter.is_valid()) {
        return iter.get_value();
    }
    else return nullptr;
}
/*
vector<User*> UserDatabase::getUsers() const {
    return m_users;
}

TreeMultimap<string, User*> UserDatabase::getMap() const {
    return m_map;
}
*/