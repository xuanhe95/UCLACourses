#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"
#include "Recommender.h"
#include <iostream>
#include <string>
using namespace std;

//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.

const string USER_DATAFILE  = "users.txt";
const string MOVIE_DATAFILE = "movies.txt";
/*
int main()
{
	UserDatabase udb;
	if (!udb.load(USER_DATAFILE))  // In skeleton, load always return false
	{
		cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
		return 1;
	}
	for (;;)
	{
		cout << "Enter user email address (or quit): ";
		string email;
		getline(cin, email);
		if (email == "quit")
			return 0;
		User* u = udb.get_user_from_email(email);
		if (u == nullptr)
			cout << "No user in the database has that email address." << endl;
		else
			cout << "Found " << u->get_full_name() << endl;
	}
}
*/

/*
//test UserDatabase
const string USER_DATAFILE = "users.txt";
const string MOVIE_DATAFILE = "movies.txt";

int main() {
    UserDatabase dbs;
    if (!dbs.load(USER_DATAFILE))  // In skeleton, load always return false
    {
        cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
        return 1;
    }
    User* userPtr1 = dbs.getUsers()[0]; // test whether program can get first name in data
    cout << userPtr1->get_full_name() << endl;
    cout << userPtr1->get_email() << endl;
    User* userPtr2 = dbs.getUsers()[1];
    cout << userPtr2->get_full_name() << endl;
    cout << userPtr2->get_email() << endl;
    TreeMultimap <std::string, User*> userMap = dbs.getMap();   
    TreeMultimap<std::string, User*>::Iterator itUser = dbs.getMap().find("AbFow2483@charter.net");
    cout << itUser.is_valid() << endl;
    User* userPtr = itUser.get_value();
    //    User* userPtr = dbs.get_user_from_email("climberkip@gmail.com");
    cout << userPtr->get_full_name() << endl;
    vector<string> watch_history = userPtr->get_watch_history();
    for (int i = 0; i < watch_history.size(); i++) {
        cout << watch_history[i] << endl;
    }
}
*/

/*
int main() {
    MovieDatabase movies;
    if (!movies.load(MOVIE_DATAFILE))  // In skeleton, load always return false
    {
        cout << "Failed to load user data file " << MOVIE_DATAFILE << "!" << endl;
        return 1;
    }
    cout << movies.get_movie_from_id("ID00001")->get_title() << endl;
    cout << movies.get_movie_from_id("ID00003")->get_title() << endl;
    cout << movies.get_movie_from_id("ID00005")->get_title() << endl;
    vector<Movie*> Tobias = movies.get_movies_with_actor("Hugo Weaving");
    for (int i = 0; i < Tobias.size(); i++) {
        cout << Tobias[i]->get_title() << endl;
    }
    cout << "===========================================" << endl;
    vector<Movie*> Harald = movies.get_movies_with_director("Robert Zemeckis");
    for (int i = 0; i < Harald.size(); i++) {
        cout << Harald[i]->get_title() << endl;
    }
}
*/


/*
int main() {
    vector<string> movies1;
    movies1.push_back("ID22937");
    movies1.push_back("ID04742");
    movies1.push_back("ID02001");
    User user1 = User("Abdullah Fowler", "AbFow2483@charter.net", movies1);
    cout << user1.get_email() << endl;
    cout << user1.get_full_name() << endl;
    vector<string> movies1_1;
    movies1_1 = user1.get_watch_history();
    cout << movies1.size() <<endl;
    cout << movies1[0] << " " << movies1[1] << " " << movies1[2] << endl;
    cout << movies1_1[0] << " " << movies1_1[1] << " " << movies1_1[2] <<endl;
}
*/


/*
//test treemm
int main() {
    TreeMultimap<std::string, int> tmm;
    tmm.insert("carey", 5);
    tmm.insert("carey", 6);
    tmm.insert("carey", 7);
    tmm.insert("david", 25);
    tmm.insert("david", 425);
    tmm.insert("david", 25);
    tmm.insert("abcd", 1);

    TreeMultimap<std::string, int>::Iterator it_1 = tmm.find("carey");
    // prints 5, 6, and 7 in some order
    int i = 0;
    while (it_1.is_valid() && i < 10) {
        std::cout << it_1.get_value() << std::endl;
        it_1.advance();
        i++;
    }

    TreeMultimap<std::string, int>::Iterator it_2 = tmm.find("laura");
    if (!it_2.is_valid())
        std::cout << "laura is not in the multimap!\n";

    TreeMultimap<std::string, User*> users;
    vector<string> watch_list1;
    watch_list1.push_back("movie1");
    watch_list1.push_back("movie2");
    string email1 = "email1";
    User* user1 = new User("name1", email1, watch_list1);
    users.insert(email1, user1);

    vector<string> watch_list2;
    watch_list2.push_back("movie3");
    watch_list2.push_back("movie4");
    watch_list2.push_back("movie5");
    string email2 = "email2";
    User* user2 = new User("name2", email1, watch_list1);
    users.insert(email2, user2);

    TreeMultimap<std::string, User*>::Iterator itUser = users.find(email2);
    std::cout << itUser.get_value()->get_full_name() << std::endl;

}

*/

#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"
#include "Recommender.h"
#include <iostream>
#include <string>
using namespace std;

//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.



int main()
{
    UserDatabase udb;
    if (!udb.load(USER_DATAFILE))  // In skeleton, load always return false
    {
        cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
        return 1;
    }

    MovieDatabase mdb;
    if (!mdb.load(MOVIE_DATAFILE))  // In skeleton, load always return false
    {
        cout << "Failed to load movie data file " << MOVIE_DATAFILE << "!" << endl;
        return 1;
    }

    // test User, UserDatabase
    cout << "Enter user email address (or quit): ";
    string email;
    getline(cin, email);
    if (email == "quit")
        return 0;
    User* u = udb.get_user_from_email(email);
    if (u == nullptr) {
        cout << "No user in the database has that email address." << endl;
        return 0;
    }
    else {
        cout << "Found " << u->get_full_name() << endl;
        cout << "Found his/her email" << u->get_email() << endl;
        cout << "Found his/her watching history " << endl;
        for (int i = 0; i < u->get_watch_history().size(); i++) {
            cout << u->get_watch_history().at(i) << ": ";
            cout << mdb.get_movie_from_id(u->get_watch_history().at(i))->get_title() << endl;
        }

    }

    // test Movie, MovieDatabase
    cout << endl << "Enter the number of movies wanted: ";
    string num;
    getline(cin, num);
    int number = stof(num);

    cout << "the number of movies to recommend is " << number << endl;

    Recommender r(udb, mdb);
    vector<MovieAndRank> recommendations = r.recommend_movies(u->get_email(), number);

    cout << "the recommendation size is " << recommendations.size() << endl;

    if (recommendations.empty()) {
        cout << "We found no movies to recommend :(." << endl;
        return 0;
    }
    else {
        cout << "We recommend the following movies: " << endl << endl;
        for (int i = 0; i < recommendations.size(); i++) {
            const MovieAndRank& mr = recommendations.at(i);
            Movie* m = mdb.get_movie_from_id(mr.movie_id);
            cout << i + 1 << ". " << m->get_title() << " ("
                << m->get_release_year() << ")\n Rating: "
                << m->get_rating() << "\n Compatibility Score: "
                << mr.compatibility_score << "\n";
            cout << endl;
        }
    }
}

/*
int main() {
    vector<string> watch_list1;
    watch_list1.push_back("movie1");
    watch_list1.push_back("movie2");
    string email1 = "email1";
    User* user1 = new User("name1", email1, watch_list1);

    vector<string> watch_list2;
    watch_list2.push_back("movie3");
    watch_list2.push_back("movie4");
    watch_list2.push_back("movie5");
    string email2 = "email2";
    User* user2 = new User("name2", email1, watch_list1);

    std::cout << user2->get_email() << endl;
    cout << user2->get_full_name() << endl;
    //cout << user2->get_watch_history() << endl;

}
*/
/*
int main() {
    TreeMultimap<std::string, int> tmm;
    tmm.insert("carey", 0);
    tmm.insert("carey", 1);
    tmm.insert("carey", 2);
    tmm.insert("Carey", 10);
    tmm.insert("david", 25);
    tmm.insert("david", 425);
    tmm.insert("david", 25);
    tmm.insert("abcd", 1);

    TreeMultimap<std::string, int>::Iterator it_1 = tmm.find("carey");
    // prints 5, 6, and 7 in some order
    int i = 0;
    while (it_1.is_valid() && i < 10) {
        std::cout << it_1.get_value() << std::endl;
        it_1.advance();
        i++;
    }

    TreeMultimap<std::string, int>::Iterator it_2 = tmm.find("laura");
    if (!it_2.is_valid())
        std::cout << "laura is not in the multimap!\n";

    TreeMultimap<std::string, User*> users;
    vector<string> watch_list1;
    watch_list1.push_back("movie1");
    watch_list1.push_back("movie2");
    string email1 = "email1";
    User* user1 = new User("name1", email1, watch_list1);
    users.insert(email1, user1);

    vector<string> watch_list2;
    watch_list2.push_back("movie3");
    watch_list2.push_back("movie4");
    watch_list2.push_back("movie5");
    string email2 = "email2";
    User* user2 = new User("name2", email1, watch_list1);
    users.insert(email2, user2);

    TreeMultimap<std::string, User*>::Iterator itUser = users.find(email2);
    std::cout << itUser.get_value()->get_full_name() << std::endl;

}*/