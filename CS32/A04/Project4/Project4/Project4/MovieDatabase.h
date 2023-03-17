#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>

#include <iostream>
#include <fstream>
#include <sstream>
#include "treemm.h"

class Movie;

class MovieDatabase
{
  public:
    MovieDatabase();
    ~MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

  private:
      TreeMultimap<std::string, Movie*> m_IDs;
      TreeMultimap<std::string, Movie*> m_Directors;
      TreeMultimap<std::string, Movie*> m_Actors;
      TreeMultimap<std::string, Movie*> m_Genres;
      std::vector<Movie*> m_movies;

      std::vector<Movie*> get_list (const std::string&, const std::string&) const;
      std::vector<std::string> get_splited_list(const std::string&);

};

#endif // MOVIEDATABASE_INCLUDED
