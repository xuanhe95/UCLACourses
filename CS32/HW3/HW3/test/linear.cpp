
#include <iostream>
using namespace std;

bool somePredicate(double x) {
    return x > 30;
}


//=================== COMMENT OUT UP ====================

// Return true if the somePredicate function returns true for at
// least one of the array elements; return false otherwise.
bool anyTrue(const double a[], int n)
{
    if (n < 1) return false; // if no elements return false
    if (somePredicate(a[n - 1])) return true;
    else return anyTrue(a, n - 1); // recursivly find true
}

// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const double a[], int n)
{
    if (n < 1) return 0; // if no elements, we got 0 true
    if (somePredicate(a[n - 1])) return countTrue(a, n - 1) + 1; // recursively return one more count
    else return countTrue(a, n - 1);   // recursively return but don't add number to count
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const double a[], int n)
{
    if (n < 1) return -1;    // if no elements return -1
    if (somePredicate(a[n - 1]) && firstTrue(a, n - 1) == -1) {
        return n - 1; // if current element is true and no more element in sub array
    }
    else return firstTrue(a, n - 1);
}

// Return the subscript of the smallest element in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told that no doubles are to
// be considered in the array, return -1.
int indexOfMinimum(const double a[], int n)
{

    if (n < 1) return -1;    // if invalid return -1
    // if current number less than sub-array's min or there is no sub array, return it self
    if (n == 1 || a[n - 1] < a[indexOfMinimum(a, n - 1)]) return n - 1;
    else return indexOfMinimum(a, n - 1);    // else return it sub array's min
}

// If all n1 elements of a1 appear in the n2 element array a2, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 is not a
// not-necessarily-contiguous subsequence of a2), return false.
// (Of course, if a1 is empty (i.e., n1 is 0), return true.)
// For example, if a2 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a1 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a1 is
//    50 30 20
// or
//    10 20 20

bool isIn(const double a1[], int n1, const double a2[], int n2)
{
    if (n2 < n1) return false;   // if n2 has less elements than n1, return false
    if (n1 == 0) return true;    // if there are no more elements in n1, return true
    if (a1[n1 - 1] == a2[n2 - 1]) return isIn(a1, n1 - 1, a2, n2 - 1);   // if find one, compare both their sub array
    else return isIn(a1, n1, a2, n2 - 1); // else a1 will keep same, just search the sub array of a1
}

//=================== COMMENT OUT DOWN ====================

int main() {
    double x[] = { 10, 50, 40, 20, 50, 40, 30 };
    int n = 7;

    cout << anyTrue(x, n) << endl;
    cout << countTrue(x, n) << endl;
    cout << firstTrue(x, n) << endl;
    cout << indexOfMinimum(x, n) << endl;

    double y[] = { 50, 40, 40 };
    double z[] = { 50, 30, 20 };
    cout << isIn(y, 3, x, n) << endl;
    cout << isIn(z, 3, x, n) << endl;
}

