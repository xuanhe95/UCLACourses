#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"

#include "User.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    m_users = &user_database;
    m_movies = &movie_database;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count)
{
    User* user = m_users->get_user_from_email(user_email);
    vector<string> historyMovies = user->get_watch_history();
    map<string, MovieAndRank> recommendedMovies;
    for (int i = 0; i < historyMovies.size(); i++) {
        Movie* movie = m_movies->get_movie_from_id(historyMovies[i]);





        vector<string> directors = movie->get_directors();
        for (int i = 0; i < directors.size(); i++) {
            vector<Movie*> movies = m_movies->get_movies_with_director(directors.at(i));
            for (int j = 0; j < movies.size(); j++) {
                string ID = movies.at(j)->get_id();
                map<string, MovieAndRank>::iterator iter = recommendedMovies.find(ID);
                if (iter == recommendedMovies.end()) recommendedMovies.insert(make_pair(ID, MovieAndRank(ID, 20)));  // if no movie yet, add it
                else iter->second.compatibility_score += 20; // else add score to it
            }
        }

        vector<string> actors = movie->get_actors();
        for (int i = 0; i < actors.size(); i++) {
            vector<Movie*> movies = m_movies->get_movies_with_actor(actors.at(i));
            for (int j = 0; j < movies.size(); j++) {
                string ID = movies.at(j)->get_id();
                map<string, MovieAndRank>::iterator iter = recommendedMovies.find(ID);
                if (iter == recommendedMovies.end()) recommendedMovies.insert(make_pair(ID, MovieAndRank(ID, 30)));  // if no movie yet, add it
                else iter->second.compatibility_score += 30; // else add score to it
            }
        }

        vector<string> genres = movie->get_genres();
        for (int i = 0; i < genres.size(); i++) {
            vector<Movie*> movies = m_movies->get_movies_with_genre(genres.at(i));
            for (int j = 0; j < movies.size(); j++) {
                string ID = movies.at(j)->get_id();
                map<string, MovieAndRank>::iterator iter = recommendedMovies.find(ID);
                if (iter == recommendedMovies.end()) recommendedMovies.insert(make_pair(ID, MovieAndRank(ID, 1)));  // if no movie yet, add it
                else iter->second.compatibility_score += 1; // else add score to it
            }
        }
    }

    // filtering out watched movies
    for (int i = 0; i < historyMovies.size(); i++) {
        map<string, MovieAndRank>::iterator iter = recommendedMovies.find(historyMovies.at(i));
        if (iter != recommendedMovies.end()) {
            recommendedMovies.erase(iter);
        }
    }

    map<string, MovieAndRank>::iterator iter = recommendedMovies.begin();
    vector<MovieAndRank> ret;
    while (iter != recommendedMovies.end()) {
        ret.push_back(iter->second);
        iter++;
    }

    sort(ret.begin(), ret.end(),
        [this](const MovieAndRank& a, const MovieAndRank& b) {
            if (a.compatibility_score != b.compatibility_score) {
                return a.compatibility_score > b.compatibility_score;
            }
            else {  // compare ratings
                Movie* movieA = m_movies->get_movie_from_id(a.movie_id);
                Movie* movieB = m_movies->get_movie_from_id(b.movie_id);
                if (movieA->get_rating() != movieB->get_rating()) {
                    return movieA->get_rating() > movieB->get_rating();
                }
                else {   // compare alphabetical order
                    return movieA->get_title() < movieB->get_title();
                }
            }
    });

    if (movie_count <= 0) {
        return vector<MovieAndRank>();
    }
    else if (ret.size() > movie_count) {
        return vector<MovieAndRank>(ret.begin(), ret.begin() + movie_count);
    }
    else {
        return ret;
    }
}

