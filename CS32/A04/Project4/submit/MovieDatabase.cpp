#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>
using namespace std;

MovieDatabase::MovieDatabase()
{

}

MovieDatabase::~MovieDatabase() {
    vector<Movie*>::iterator iter = m_movies.begin();
    while (iter != m_movies.end()) {
        Movie* movie = *iter;
        iter = m_movies.erase(iter);
        delete movie;
    }
}

bool MovieDatabase::load(const string& filename)
{
    ifstream data(filename);
    if (!data.is_open()) return false;

    string ID;
    string title;
    string year;
    string director;
    string actor;
    string genre;
    string rating;
    string emptyLine;

    while (getline(data, ID)) {
        getline(data, title);
        getline(data, year);
        getline(data, director);
        getline(data, actor);
        getline(data, genre);
        getline(data, rating);
        //getline(data, emptyLine);


        vector<string> directors = get_splited_list(director);
        vector<string> actors = get_splited_list(actor);
        vector<string> genres = get_splited_list(genre);

        Movie* movie = new Movie(   // create new movie
            ID, title, year, directors,
            actors, genres, stof(rating));

        m_movies.push_back(movie);

        //maintain maps
        m_IDs.insert(ID, movie);
        //cout << m_IDs.find(ID).get_value()->get_title() << endl;
        for (int i = 0; i < directors.size(); i++) {
            m_Directors.insert(directors[i], movie);
        }
        for (int i = 0; i < actors.size(); i++) {
            m_Actors.insert(actors[i], movie);
        }
        for (int i = 0; i < genres.size(); i++) {
            m_Genres.insert(genres[i], movie);
        }
        
        if (!getline(data, emptyLine)) {
            break; // end of file
        }
    }

    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    TreeMultimap<std::string, Movie*>::Iterator iter = m_IDs.find(id);
    if(iter.is_valid()){
        return iter.get_value();
    }
    return nullptr;
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    return get_list(director, "director");
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    return get_list(actor, "actor");
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    return get_list(genre, "genre");
}

vector<Movie*> MovieDatabase::get_list(const string& name, const string& type) const {
    vector<Movie*> ret;
    TreeMultimap<std::string, Movie*>::Iterator iter;
    if (type == "director") {
        iter = m_Directors.find(name);
    }
    else if (type == "actor") {
        iter = m_Actors.find(name);
    }
    else if (type == "genre") {
        iter = m_Genres.find(name);
    }
    
    while (iter.is_valid()) {
        ret.push_back(iter.get_value());
        iter.advance();
    }
    return ret;
}

vector<string> MovieDatabase::get_splited_list(const string& data) {
    vector<string> ret;
    stringstream line(data);
    string word;
    while (getline(line, word, ',')) {
        ret.push_back(word);
    }
    return ret;
}