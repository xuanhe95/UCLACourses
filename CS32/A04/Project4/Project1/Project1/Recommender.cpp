#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    user_data = &user_database;
    movie_data = &movie_database;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    // get the past watching history of the specific user
    User* m_user = user_data->get_user_from_email(user_email);
    vector<string> movie_history = m_user->get_watch_history();

    map<string, MovieAndRank> recommended_movies;
    
    for (int i = 0; i < movie_history.size(); i++){
        Movie* m_movie_history = movie_data->get_movie_from_id(movie_history.at(i));

        // Determine compatibility score of directors
        vector<string> m_directors = m_movie_history->get_directors();
        for (int j = 0; j < m_directors.size(); j++){
            vector<Movie*> m_movies = movie_data->get_movies_with_director(m_directors.at(j));
            for (int k = 0; k < m_movies.size(); k++){
                string m_id = m_movies.at(k)->get_id();
                map<string, MovieAndRank>::iterator it = recommended_movies.find(m_id);
                if (it != recommended_movies.end()) // currently exist in the map
                    it->second.compatibility_score += 20;
                else // currently not in the map
                    recommended_movies.insert(make_pair(m_id, MovieAndRank(m_id, 20)));
            }
        }

        // Determine compatibility score of actors
        vector<string> m_actors = m_movie_history->get_actors();
        for (int j = 0; j < m_actors.size(); j++){
            vector<Movie*> m_movies = movie_data->get_movies_with_actor(m_actors.at(j));
            for (int k = 0; k < m_movies.size(); k++){
                string m_id = m_movies.at(k)->get_id();
                map<string, MovieAndRank>::iterator it = recommended_movies.find(m_id);
                if (it != recommended_movies.end()) // currently exist in the map
                    it->second.compatibility_score += 30;
                else // currently not in the map
                    recommended_movies.insert(make_pair(m_id, MovieAndRank(m_id, 30)));
            }
        }

        // Determine compatibility score of genres
        vector<string> m_genres = m_movie_history->get_genres();
        for (int j = 0; j < m_genres.size(); j++){
            vector<Movie*> m_movies = movie_data->get_movies_with_genre(m_genres.at(j));
            for (int k = 0; k < m_movies.size(); k++){
                string m_id = m_movies.at(k)->get_id();
                map<string, MovieAndRank>::iterator it = recommended_movies.find(m_id);
                if (it != recommended_movies.end()) // currently exist in the map
                    it->second.compatibility_score += 1;
                else // currently not in the map
                    recommended_movies.insert(make_pair(m_id, MovieAndRank(m_id, 1)));
            }
        }
    }


    // delete the ones in watching history
    for (int i = 0; i < movie_history.size(); i++){
        map<string, MovieAndRank>::iterator it = recommended_movies.find(movie_history.at(i));
        if (it != recommended_movies.end()){
            recommended_movies.erase(it);
        }
    }

    // make this into a vector
    vector<MovieAndRank> potential_list;
    map<string, MovieAndRank>::iterator it = recommended_movies.begin();
    while (it != recommended_movies.end()){
        potential_list.push_back(it->second);
        it++;
    }

    sort(potential_list.begin(), potential_list.end(), [this](const MovieAndRank& a, const MovieAndRank& b){
        if (a.compatibility_score != b.compatibility_score)
            return a.compatibility_score > b.compatibility_score;
        else{
            // compare by movies rating
            Movie* m_a = movie_data->get_movie_from_id(a.movie_id);
            Movie* m_b = movie_data->get_movie_from_id(b.movie_id);
            if (m_a->get_rating() != m_b->get_rating())
                return m_a->get_rating() > m_b->get_rating();
            else
                // compare by alphabetical order
                return m_a->get_title() < m_b->get_title();
        }
    });

    if (movie_count <= 0)
        return vector<MovieAndRank>();
    else if (potential_list.size() < movie_count){
        return potential_list;
    }
    else
        return vector<MovieAndRank>(potential_list.begin(), potential_list.begin()+movie_count);
}
