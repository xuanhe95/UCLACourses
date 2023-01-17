
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int split(string a[], int n, string splitter);

int main() {
    string h[7] = { "rishi", "margaret", "gordon", "tony", "", "john", "liz" };
    // Test whether lookup() works normally when n > 0 and there is a matching string
    assert(lookup(h, 7, "john") == 5);
    // Test whether lookup() works normally when n > 0 and there is a matching string
    assert(lookup(h, 7, "gordon") == 2);
    // Test whether lookup() works normally when n > 0 and there is no matching string
    assert(lookup(h, 2, "gordon") == -1);
    // Test whether lookup() works normally when n = 0
    assert(lookup(h, 0, "gordon") == -1);
    // Test whether lookup() works normally when n < 0
    assert(lookup(h, -2, "gordon") == -1);
    
    // Test whether positionOfMax() works normally when n > 0
    assert(positionOfMax(h, 7) == 3);
    // Test whether positionOfMax() works normally when n > 0
    assert(positionOfMax(h, 2) == 0);
    // Test whether positionOfMax() works normally when n = 0
    assert(positionOfMax(h, 0) == -1);
    // Test whether positionOfMax() works normally when n < 0
    assert(positionOfMax(h, -2) == -1);
    
    // Test whether split() works normally when n > 0
    assert(split(h, 7, "liz") == 3);
    // Test whether split() works normally when n > 0 and there is no value > spliter
    assert(split(h, 5, "zh") == 5);
    // Test whether split() works normally when n = 0
    assert(split(h, 0, "liz") == 0);
    // Test whether split() works normally when n < 0
    assert(split(h, -2, "liz") == -1);
    
    string i[7] = { "rishi", "margaret", "gordon", "tony", "", "john", "liz" };
    string g[4] = { "rishi", "margaret", "liz", "theresa" };
    // Test whether differ() works normally when n1 > 0 and n2 > 0
    assert(differ(i, 4, g, 4) == 2);
    // Test whether differ() works normally when n1 > 0 and n2 > 0
    assert(differ(i, 1, g, 4) == 1);
    // Test whether differ() works normally when n1 = 0 or n2 = 0
    assert(differ(i, 1, g, 0) == 0);
    // Test whether differl() works normally when n1 < 0 or n2 < 0
    assert(differ(i, -1, g, 0) == -1);
    
    // Test whether appendToAll() works normally when n > 0
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "rishi?" && g[3] == "theresa?");
    // Test whether appendToAll() works normally when n = 0
    assert(appendToAll(g, 0, "?") == 0 && g[0] == "rishi?" && g[3] == "theresa?");
    // Test whether appendToAll() works normally when n < 0
    assert(appendToAll(g, -4, "?") == -1);
    
    string newg[4] = { "rishi", "margaret", "liz", "theresa" };
    // Test whether rotateLeft() works normally when n-1 = pos
    assert(rotateLeft(newg, 2, 1) == 1 && newg[1] == "margaret" && newg[3] == "theresa");
    // Test whether rotateLeft() works normally when n > 0
    assert(rotateLeft(newg, 4, 1) == 1 && newg[1] == "liz" && newg[3] == "margaret");
    // Test whether rotateLeft() works normally when n-1 < pos
    assert(rotateLeft(newg, 2, 2) == -1);
    // Test whether rotateLeft() works normally when n < 0
    assert(rotateLeft(newg, -4, 1) == -1);
    // Test whether rotateLeft() works normally when pos < 0
    assert(rotateLeft(newg, 4, -1) == -1);

    string e[4] = { "gordon", "tony", "", "john" };
    // Test whether subsequence() works normally when n1 > 0 and n2 > 0 and n1 > n2
    assert(subsequence(i, 7, e, 4) == 2);
    // Test whether subsequence() works normally when n1 = 0 and n2 > 0
    assert(subsequence(i, 0, e, 2) == -1);
    // Test whether subsequence() works normally when n2 = 0 and n1 > 0
    assert(subsequence(i, 2, e, 0) == 0);
    // Test whether subsequence() works normally when n1 = 0 and n2 = 0
    assert(subsequence(i, 0, e, 0) == 0);
    // Test whether subsequence() works normally when n1 < n2
    assert(subsequence(i, 2, e, 4) == -1);
    // Test whether subsequence() works normally when n2 < 0
    assert(subsequence(i, 7, e, -4) == -1);
    string newh[8] = { "rishi", "margaret", "gordon", "gordon", "tony", "", "john", "liz" };
    // Test whether subsequence() works normally when same element occurs twice
    assert(subsequence(newh, 8, e, 4) == 3);
    
    string d[5] = { "margaret", "margaret", "margaret", "tony", "tony" };
    // Test whether countRuns() works normally when n > 0
    assert(countRuns(d, 5) == 2);
    // Test whether countRuns() works normally when n = 0
    assert(countRuns(d, 0) == 0);
    // Test whether countRuns() works normally when n < 0
    assert(countRuns(d, -5) == -1);

    string f[3] = { "liz", "gordon", "tony" };
    // Test whether lookupAny() works normally when n1 > 0 and n2 > 0
    assert(lookupAny(i, 7, f, 3) == 2);
    // Test whether lookupAny() works normally when n1 > 0 and n2 > 0
    assert(lookupAny(i, 1, f, 3) == -1);
    // Test whether lookupAny() works normally when n1 = 0 or n2 = 0
    assert(lookupAny(i, 7, f, 0) == -1);
    // Test whether lookupAny() works normally when n1 < 0 or n2 < 0
    assert(lookupAny(i, -7, f, 2) == -1);
    
    // Test whether flip() works normally when n > 0
    assert(flip(f, 3) == 3 && f[0] == "tony" && f[2] == "liz");
    // Test whether flip() works normally when n > 0
    assert(flip(f, 2) == 2 && f[0] == "gordon" && f[2] == "liz");
    // Test whether flip() works normally when n = 0
    assert(flip(f, 0) == 0 && f[0] == "gordon" && f[2] == "liz");
    // Test whether flip() works normally when n < 0
    assert(flip(f, -3) == -1);
    

    cout << "All tests succeeded" << endl;
    return 0;
}

int appendToAll(string a[], int n, string value) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 0;
    }
    for (int i = 0; i < n; i ++) {
        a[i] = a[i] + value;
    }
    return n;
}

int lookup(const string a[], int n, string target) {
    if (n > 0) {
        for (int i = 0; i < n; i ++) {
            if (a[i] == target) {
                return i;
            }
        }
    }
    return -1;
}

int positionOfMax(const string a[], int n) {
    if (n > 0) {
        // create a max value and update it
        string max = a[0];
        for (int i = 0; i < n; i ++) {
            if (a[i] >= max) {
                max = a[i];
            }
        }
        for (int i = 0; i < n; i ++) {
            if (a[i] == max) {
                return i;
            }
        }
    }
    return -1;
}

int rotateLeft(string a[], int n, int pos) {
    if (pos == n-1) {
        return pos;
    }
    if (n > 0 && pos > 0 && pos < n-1) {
        // duplicate a[]
        string b[10000];
        for (int i = 0; i < n; i++) {
            b[i] = a[i];
        }
        // put the item that was thus eliminated into the last position of the array
        a[n-1] = b[pos];
        // copying all elements after it one place to the left
        for (int i = pos; i < n-1; i++) {
            a[i] = b[i+1];
        }
        return pos;
    }
    return -1;
}

int countRuns(const string a[], int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    if (n > 1) {
        // count the number of sequences that is not consecutive and plus 1
        int count = 1;
        for (int i = 0; i < n - 1; i++) {
            if (a[i] != a[i+1]) {
                count ++;
            }
        }
        return count;
    }
    return -1;
}

int flip(string a[], int n) {
    if (n == 0) {
        return 0;
    }
    if (n > 0) {
        // duplicate a[0] to a[n]
        string b[10000];
        for (int i = 0; i < n; i++) {
            b[i] = a[i];
        }
        // flip
        for (int i = 0; i < n; i++) {
            a[i] = b[n-1-i];
        }
        return n;
    }
    return -1;
}

int differ(const string a1[], int n1, const string a2[], int n2) {
    if (n1 >= 0 && n2 >= 0) {
        if (n1 == 0 || n2 == 0) {
           return 0;
        }
        // use n to represent the smaller value
        int n;
        if (n1 <= n2) {
            n = n1;
        } else {
            n = n2;
        }
        for (int i = 0; i < n; i++) {
            if (a1[i] != a2[i]) {
                return i;
            }
        }
        return n;
    }
    return -1;
}

int subsequence(const string a1[], int n1, const string a2[], int n2) {
    if (n1 >= 0 && n2 >= 0 && n2 <= n1) {
        if (n2 == 0) {
            return 0;
        }
        // count the number of different element
        int diff = 0;
        for (int i = 0; i < n1; i++) {
            // find the same initial value
            if (a1[i] == a2[0] && i+n2 <= n1) {
                for (int j = 0; j < n2; j++) {
                    if (a1[i+j] != a2[j]) {
                        diff ++;
                    }
                }
                if (diff == 0) {
                    return i;
                }
                diff = 0;
            }
        }
    }
    return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2) {
    if (n1 > 0 && n2 > 0) {
        // loop through a1 and then loop through a2 to compare
        for (int i = 0; i < n1; i++) {
            for (int j = 0; j < n2; j++) {
                if (a1[i] == a2[j]) {
                    return i;
                }
            }
        }
    }
    return -1;
}

int split(string a[], int n, string splitter) {
    if (n == 0) {
        return 0;
    }
    if (n > 0) {
        // sort a from small to large
        for (int i = 0; i < n; i++) {
            for (int i = 0; i < n-1; i++) {
                if (a[i] > a[i+1]) {
                    string b = a[i];
                    a[i] = a[i+1];
                    a[i+1] = b;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (a[i] >= splitter) {
                return i;
            }
        }
        return n;
    }
    return -1;
}

