#ifndef MOVIE_INCLUDED
#define MOVIE_INCLUDED

#include <string>
#include <vector>
#include <iostream>

class Movie
{
  public:
    Movie(const std::string& id, const std::string& title,
          const std::string& release_year,
          const std::vector<std::string>& directors,
          const std::vector<std::string>& actors,
          const std::vector<std::string>& genres, float rating);
    std::string get_id() const;
    std::string get_title() const;
    std::string get_release_year() const;
    float get_rating() const;
    std::vector<std::string> get_directors() const;
    std::vector<std::string> get_actors() const;
    std::vector<std::string> get_genres() const;
    
    void printMovie() const{
        std::cout << "movie id: " << m_ID << std::endl;
        std::cout << "movie title: " << m_title << std::endl;
        std::cout << "movie release year: " << m_release_year << std::endl;
        std::cout << "movie directors: ";
        for (int i = 0; i < m_directors.size(); i++)
            std::cout << m_directors.at(i) << "*" ;
        std::cout << std::endl << "movie actors: ";
        for (int i = 0; i < m_actors.size(); i++)
            std::cout << m_actors.at(i) << "*" ;
        std::cout << std::endl << "movie genres: ";
        for (int i = 0; i < m_genres.size(); i++)
            std::cout << m_genres.at(i) << "*" ;
        std::cout << std::endl;
        std::cout << "movie rating: " << m_rating << std::endl;
        std::cout << std::endl;
    }

  private:
    std::string m_ID;
    std::string m_title;
    std::string m_release_year;
    std::vector<std::string> m_directors;
    std::vector<std::string> m_actors;
    std::vector<std::string> m_genres;
    float m_rating;

    
};

#endif // MOVIE_INCLUDED
