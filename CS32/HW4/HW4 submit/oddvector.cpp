
    void removeOdd(vector<int>& v)
    {
        for (vector<int>::iterator it = v.begin(); it != v.end();) {
            if (*it % 2 != 0) {
                it = v.erase(it);
            }
            else {
                it++;
            }
        }
    }
