#include <iostream>
using namespace std;
void findMax(int arr[], int n, int*& pToMax);
//const char* findTheChar(const char* str, char chr);
double mean(const double*, int);
double mean2(const double*, int);
const char* findTheChar(const char str[], char chr);
const char* findTheChar2(const char* str, char chr);
const char* findTheChar3(const char* str, char chr);
void removeS(char* ptr);

/*
#include <iostream>
using namespace std;

int* nochange(int* p)
{
    return p;
}

int* getPtrToArray(int& m)
{
    int anArray[100];
    for (int j = 0; j < 100; j++)
        anArray[j] = 100 - j;
    m = 100;
    return nochange(anArray);
}

void f()
{
    int junk[100];
    for (int k = 0; k < 100; k++)
        junk[k] = 123400000 + k;
    junk[50]++;
}

int main()
{
    int n;
    int* ptr = getPtrToArray(n);
    //f();
    for (int i = 0; i < 3; i++)
        cout << ptr[i] << ' ';
    for (int i = n - 3; i < n; i++)
        cout << ptr[i] << ' ';
    cout << endl;
}
*/
/*
int main()
{
    char msg[50] = "She'll shave a massless princess.";
    removeS(msg);
    cout << msg;  // prints   he'll have a male prince.
}

void removeS(char* ptr)
{
    char* str = ptr;	//let str to point the same position with ptr
    while (*ptr != 0) {	//while loop until the value of ptr is 0
        while (*ptr == 'S' || *ptr == 's') {
            //while the value that ptr points to is 'S' or 's'
            ptr++;	//move pointer to point next position
        }
        *str = *ptr;  //assign value of ptr to the position that str points to
        str++;  //move str to point next position
        ptr++;  //move ptr to point next position
    }
    *str = 0;   //let the value that str points equal to 0 to end the C string
}
*/
/*
int main()
{
    char msg[50] = "She'll shave a massless princess.";
    removeS(msg);
    cout << msg;  // prints   he'll have a male prince.
}

void removeS(char* ptr)
{
    char* str = ptr;
    //let str to point the head of the C string ptr
    while (*ptr != 0) {
        //while loop until ptr points to 0
        while (*ptr == 'S' || *ptr == 's') {
            //while the value that ptr points to is 'S' or 's'
            ptr++;
            //move pointer to point next position
        }
        *str = *ptr;
        //assign value of ptr to the position that str points to
        str++;  //move str to point next position
        ptr++;  //move ptr to point next position
    }
    *str = 0;   //let str points to 0 to end the C string
}
*/



/*

double mean(const double* scores, int numScores)
{
    const double* ptr = scores;
    double tot = 0;
    while (ptr != scores + numScores)
    {
        tot += *ptr;
        ptr++;
    }
    return tot / numScores;
}

double mean2(const double* scores, int numScores) {
    const double* ptr = scores;
    double tot = 0;
    int i = 0;
    while (i < numScores)
    {
        tot += *(ptr + i);
        i++;
    }
    return tot / numScores;

}

int main() {
    const double scores[4] = { 1, 4, 5, 7};
    cout << mean(scores, 4) << endl;
    cout << mean2(scores, 4) << endl;
}
*/

/*

int main() {
    const char str[20] = "pienapple";
    cout << "First: " << *findTheChar(str, 'p') << endl;
    cout << "Next..." << endl;
    const char str2[20] = "pienapple";
    cout << "Second: " << *findTheChar2(str2, 'p') << endl;
    cout << "Last: " << *findTheChar3(str, 'p') << endl;
    cout << "THE END" << endl;
}


// This function searches through str for the character chr.
// If the chr is found, it returns a pointer into str where
// the character was first found, otherwise nullptr (not found).

const char* findTheChar(const char str[], char chr)
{
    for (int k = 0; str[k] != 0; k++)
        if (str[k] == chr)
            return &str[k];

    return nullptr;
}

const char* findTheChar2(const char* str, char chr) {
    for (int k = 0; *str != 0; k++) {
        if (*(str + k) == chr)
            return str + k;
    }
    return nullptr;
}

const char* findTheChar3(const char* str, char chr) {
    while (*str != 0) {
        if (*str == chr)
            return str;
        str++;
    }
    return nullptr;
}

*/
/*
int main() {
    double* cat;
    //Declare a pointer variable named cat that can point to a variable of type double.
    double mouse[5];
    //Declare mouse to be a 5-element array of doubles.
    cat = &mouse[4];
    //Make the cat variable point to the last element of mouse.
    *cat = 25;
    //Make the double pointed to by cat equal to 25, using the * operator.
    *(mouse + 3) = 54;
    //Without using the cat pointer, and without using square brackets, set the fourth element
    //(i.e., the one at position 3) of the mouse array to have the value 54.
    cat -= 3;
    //Move the cat pointer back by three doubles.
    cat[1] = 42;
    //Using square brackets, but without using the name mouse, set the third element
    //(i.e., the one at position 2) of the mouse array to have the value 42. (You may use cat.)
    cat[0] = 17;
    //Without using the* operator or the name mouse, but using square brackets, set the double pointed to by cat to have the value 17.
    bool d = (cat == mouse);
    //Using the == operator in the initialization expression,
    //declare a bool variable named d and initialize it with an expression that evaluates to true
    //if cat points to the double at the start of the mouse array, and to false otherwise.
    bool b = (*cat == *(cat + 1));
    //Using the * operator in the initialization expression,
    //declare a bool variable named b and initialize it with an expression that evaluates to true
    //if the double pointed to by cat is equal to the double immediately following the double pointed to by cat, and to false otherwise.
    //Do not use the name mouse.
    for (int i = 0; i < 5; i++) {
        cout << mouse[i] << endl;
    }
}
*/

/*
int main()
{
    int arr[3] = { 5, 10, 15 };
    int* ptr = arr;

    *ptr = 10;          // set arr[0] to 10
    *(ptr + 1) = 20;      // set arr[1] to 20
// add 1 to the pointer first then dereference the pointer to set right value
    ptr += 2;
    ptr[0] = 30;        // set arr[2] to 30

    while (ptr >= arr)
    {
        cout << *ptr << endl;    // print values
        ptr--;	//the order of abstraction was wrong
    }
}*/


/**

void findMax(int arr[], int n, int*& pToMax)
{
    if (n <= 0)
        return;      // no items, no maximum!

    pToMax = arr;

    for (int i = 1; i < n; i++)
    {
        if (arr[i] > *pToMax)
            pToMax = arr + i;
    }
}

int main()
{
    int nums[4] = { 5, 3, 15, 6 };
    int* ptr = &nums[0];

    findMax(nums, 4, ptr);
    cout << "The maximum is at address " << ptr << endl;
    cout << "It's at position " << ptr - nums << endl;
    cout << "Its value is " << *ptr << endl;
}*/


/*

void computeCube(int n, int* ncubed)
{
    *ncubed = n * n * n;
}

int main()
{
    int i;	//we need to assign a memory address to the pointer
    int* ptr = &i;
    computeCube(5, ptr);
    cout << "Five cubed is " << *ptr << endl;
}*/

/*
      // return true if two C strings are equal
    bool strequal(const char str1[], const char str2[])
    {
        while (*str1 != 0  &&  *str2 != 0)  // zero bytes at ends
        {
            if (*str1 != *str2)  // compare corresponding characters
                return false;
            str1++;            // advance to the next character
            str2++;
        }
        return *str1 == *str2;   // both ended at same time?
    }

    int main()
    {
        char a[15] = "Chang";
        char b[15] = "Zhang";

        if (strequal(a,b))
            cout << "They're the same person!\n";
    }
*/



/*
double mean(const double* scores, int numScores)
{
    const double* ptr = scores;
    double tot = 0;
    int i = 0;
    while ((ptr + i) != scores + numScores)
    {
        tot += *(ptr + i);
        i++;
    }
    return tot / numScores;
}

int main()
{
    const double arr[3] = { 1, 3, 5 };
    double m = mean(arr, 3);
    cout << m << endl;
}
*/

// This function searches through str for the character chr.
    // If the chr is found, it returns a pointer into str where
    // the character was first found, otherwise nullptr (not found).


/*
const char* findTheChar(const char* str, char chr)
{
    while (*str != 0) {
        if (*str == chr) return str;
        str++;
    }
    return nullptr;
}

int main() {
    const char arr[] = "banana";
    const char* ptr = findTheChar(arr, 'a');
    cout << "Result: " << ptr << endl;
}
*/