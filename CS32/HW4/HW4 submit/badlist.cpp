    void removeBad(list<Movie*>& li)
    {
        for (list<Movie*>:: iterator it = li.begin(); it != li.end(); ){
            if ((*it)->rating() < 50) {
                (*it)->~Movie();
                it = li.erase(it);
            }
            else {
                it++;
            }
        }
    }