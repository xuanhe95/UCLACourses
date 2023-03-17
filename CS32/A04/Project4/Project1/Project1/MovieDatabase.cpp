#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;


MovieDatabase::MovieDatabase()
{}

MovieDatabase::~MovieDatabase(){
    vector<Movie*>::iterator it = memory.begin();
    while (it != memory.end()){
        delete *it;
        it = memory.erase(it);
    }
}

bool MovieDatabase::load(const string& filename)
{
    //load file
    ifstream movieFile(filename);
    if (!movieFile) {
        return false;
    }
    
    string line;
    string id, title, release_year, director, actor, genre, ratingstr;
    vector<string> directors, actors, genres;
    float rating;
    
    //loop to extract information
    while (getline(movieFile, id)){
        getline(movieFile, title);
        getline(movieFile, release_year);
        getline(movieFile, director);
        directors = splitNames(director);
        getline(movieFile, actor);
        actors = splitNames(actor);
        getline(movieFile, genre);
        genres = splitNames(genre);
        getline(movieFile, ratingstr);
        rating = stof(ratingstr);       //convert string to float
        
        Movie* temp = new Movie(id, title, release_year, directors, actors, genres, rating);
        
        // for movie_ID
        movies_ID.insert(id, temp);
        
        // for movie_directors
        for (int i = 0; i < directors.size(); i++)
            movies_director.insert(directors.at(i), temp);
            
        // for movie_actors
        for (int i = 0; i < actors.size(); i++)
            movies_actor.insert(actors.at(i), temp);
            
        // for movie_genre
        for (int i = 0; i < genres.size(); i++)
            movies_genre.insert(genres.at(i), temp);
        
        memory.push_back(temp);
        
        if (!getline(movieFile, line)) {
            break; // end of file
        }
    }
    return true;
}

//use substr to split the long string into individual names
vector<string> MovieDatabase::splitNames(string line){
    vector<string> temp;
    temp.clear();
    while (line.find(',') != string::npos){
        size_t pos = line.find(',');
        temp.push_back(line.substr(0, pos));
        line = line.substr(pos+1);
    }
    temp.push_back(line);
    return temp;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    if (movies_ID.find(id).is_valid())
        return movies_ID.find(id).get_value();
    else
        return nullptr;
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    vector<Movie*> thisDirector;
    TreeMultimap<string, Movie*>::Iterator it = movies_director.find(director);
    while (it.is_valid()){
        thisDirector.push_back(it.get_value());
        it.advance();
    }
    return thisDirector;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    vector<Movie*> thisActor;
    TreeMultimap<string, Movie*>::Iterator it = movies_actor.find(actor);
    while (it.is_valid()){
        thisActor.push_back(it.get_value());
        it.advance();
    }
    return thisActor;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    vector<Movie*> thisGenre;
    TreeMultimap<string, Movie*>::Iterator it = movies_genre.find(genre);
    while (it.is_valid()){
        thisGenre.push_back(it.get_value());
        it.advance();
    }
    return thisGenre;
}
