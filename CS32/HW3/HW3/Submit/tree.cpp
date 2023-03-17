/*

#include<iostream>
using namespace std;

*/

//=================== COMMENT OUT UP ====================

// Return the number of ways that all n1 elements of a1 appear in
     // the n2 element array a2 in the same order (though not necessarily
     // consecutively).  We decree that the empty sequence (i.e. one where
     // n1 is 0) appears in a sequence of length n2 in 1 way, even if n2
     // is 0.  For example, if a2 is the 7 element array
     //    10 50 40 20 50 40 30
     // then for this value of a1     the function must return
     //    10 20 40                        1
     //    10 40 30                        2
     //    20 10 40                        0
     //    50 40 30                        3
   int countIsIn(const double a1[], int n1, const double a2[], int n2)
   {
       if (n1 == 0) return 1;   // if matched all a1 return 1
       if (n1 > n2) return 0;
       if (a1[n1 - 1] == a2[n2 - 1]) return countIsIn(a1, n1-1, a2, n2-1) + countIsIn(a1, n1, a2, n2-1);
       // if matched one item, return countIsIn contains itself add doesn't contain itself
       else return countIsIn(a1, n1, a2, n2-1); // else return doesn't contain itself
   }

     // Exchange two doubles
   void exchange(double& x, double& y)
   {
       double t = x;
       x = y;
       y = t;
   }

     // Rearrange the elements of the array so that all the elements
     // whose value is > divider come before all the other elements,
     // and all the elements whose value is < divider come after all
     // the other elements.  Upon return, firstNotGreater is set to the
     // index of the first element in the rearranged array that is
     // <= divider, or n if there is no such element, and firstLess is
     // set to the index of the first element that is < divider, or n
     // if there is no such element.
     // In other words, upon return from the function, the array is a
     // permutation of its original value such that
     //   * for 0 <= i < firstNotGreater, a[i] > divider
     //   * for firstNotGreater <= i < firstLess, a[i] == divider
     //   * for firstLess <= i < n, a[i] < divider
     // All the elements > divider end up in no particular order.
     // All the elements < divider end up in no particular order.
   void divide(double a[], int n, double divider,
                                          int& firstNotGreater, int& firstLess)
   {
       if (n < 0)
       n = 0;
   
         // It will always be the case that just before evaluating the loop
         // condition:
         //  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
         //  Every element earlier than position firstNotGreater is > divider
         //  Every element from position firstNotGreater to firstUnknown-1 is
         //    == divider
         //  Every element from firstUnknown to firstLess-1 is not known yet
         //  Every element at position firstLess or later is < divider
   
       firstNotGreater = 0;
       firstLess = n;
       int firstUnknown = 0;
       while (firstUnknown < firstLess)
       {
           if (a[firstUnknown] < divider)
           {
               firstLess--;
               exchange(a[firstUnknown], a[firstLess]);
           }
           else
           {
               if (a[firstUnknown] > divider)
               {
                   exchange(a[firstNotGreater], a[firstUnknown]);
                   firstNotGreater++;
               }
               firstUnknown++;
           }
       }
   }

     // Rearrange the elements of the array so that
     // a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
     // If n <= 1, do nothing.
   void order(double a[], int n)
   {
       if (n <= 1) return;
       int firstNotGreater, firstLess;
       divide(a, n, a[0], firstNotGreater, firstLess);
       order(a, firstNotGreater);   // arrange larger partition
       order(a + firstLess, n - firstLess); // arrange smaller parition
   }

//=================== COMMENT OUT DOWN ====================
   /*
int main(){
    double a[] = {10, 50, 40, 20, 50, 40, 30};
    double b[] = {10, 20, 40};
    double c[] = {10, 40, 30};
    double d[] = {20, 10, 40};
    double e[] = {50, 40, 30};
    int n1 = 3;
    int n2 = 7;
    cout << countIsIn(b, n1, a, n2) << endl;
    cout << countIsIn(c, n1, a, n2) << endl;
    cout << countIsIn(d, n1, a, n2) << endl;
    cout << countIsIn(e, n1, a, n2) << endl;
    
    double f[] = {10, -10, 20, 15, -20, 0};
    double g[] = {-1, -3, 3, -4, 5, 10, -10};
    order(a, 7);
    for (int i = 0; i < 7; i++){
        cout << a[i] << endl;
    }
    cout << "===========" << endl;
    order(c, 3);
    for (int i = 0; i < 3; i++){
        cout << c[i] << endl;
    }
    cout << "===========" << endl;
    order(f, 6);
    for (int i = 0; i < 6; i++) {
        cout << f[i] << endl;
    }
    cout << "===========" << endl;
    order(g, 7);
    for (int i = 0; i < 7; i++) {
        cout << g[i] << endl;
    }
}
*/