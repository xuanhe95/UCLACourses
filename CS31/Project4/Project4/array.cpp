#include <iostream>
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

void quickSort(string a[], int n, string target, int left, int right);	//helper method for split, sort arrays
int partition(string a[], int left, int right);	//helper method for quickSort, get the index of pivot that already sorted
void swap(string a[], int i, int j);	//swap two elements

// testers
void testAppendToAll();
void testLookup();
void testPositionOfMax();
void testRotateLeft();
void testCountRuns();
void testFlip();
void testDiffer();
void testSubsequence();
void testLookupAny();
void testSplit();
void print(string a[], int n);	//helper method to print arrays

int appendToAll(string a[], int n, string value) {
	if (n < 0) return -1;
	for (int i = 0; i < n; i++) a[i] += value;	//add value to each string
	return n;
}

int lookup(const string a[], int n, string target) {
	if (n < 0) return -1;
	for (int i = 0; i < n; i++)  if (a[i] == target) return i;	//if current element equals target, return its index
	return -1;
}

int positionOfMax(const string a[], int n) {
	if (n < 0) return -1;
	if (n == 0) return -1;
	int maxIndex = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] > a[maxIndex]) maxIndex = i;	//if find a bigger string, record its index
	}
	return maxIndex;
}

int rotateLeft(string a[], int n, int pos) {
	if (n < 0) return -1;
	if (pos < 0) return -1;
	if (pos > n - 1) return -1;	//if the pos itself exceed the length of array, return -1
	string temp = a[pos];	//preserve the element on pos
	for (int i = pos; i < n-1; i++) {
		a[i] = a[i + 1];	//left rotate each element after pos
	}
	a[n - 1] = temp;	//set the preserved element to last one
	return pos;
}

int countRuns(const string a[], int n) {
	if (n < 0) return -1;
	if (n == 0) return 0;	//if there is no elements, return 0
	int cnt = 1;	//start with 1 count
	for (int i = 1; i < n; i++) {	//start with the second element
		if (a[i] == a[i - 1]) continue;
		cnt++;	//if current element doesn't equal the last one, plus 1 to count
	}
	return cnt;
}

int flip(string a[], int n) {
	if (n < 0) return -1;
	for (int i = 0; i < n/2; i++){	//we just need to swap half of n pairs
		swap(a, i, n-1-i);	//swap element pairs
	}
	return n;
}

int differ(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 <0) return -1;

	for (int i = 0; i < n1 && i < n2; i++) {	//just compare the shortest one between a1 and a2
		if (a1[i] == a2[i]) continue;
		else return i;	//if two elements doesn't equal, return its index
	}

	return (n1 <= n2) ? n1 : n2;	//return the shortest n
}

int subsequence(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0) return -1;
	if (n2 == 0) return 0;	//return 0 if the second array is a sequence of 0

	int left = 0, right = 0;	//tracing the start and the end of equal parts between n1 and n2
	int indexOfA2 = 0;	//tracing the current compare element of a2
	while (left < n1 && right < n1) {
		if (a1[right] == a2[indexOfA2]) {	//if two current elements are equal, move both pointer to the next
			right++;
			indexOfA2++;
		}
		else {	//if two elements are not equal, reset indexOf2, move left to the next and reset right equals left
			indexOfA2 = 0;
			left++;
			right = left;
		}
		if (indexOfA2 == n2) return left;	//if indexOfA2 equals n2, return left
	}
	return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0) return -1;
	for (int i = 0; i < n1; i++) {	//compare each element in a1 with a2, if they are equal, return i
		for (int j = 0; j < n2; j++) {
			if (a1[i] == a2[j]) return i;
		}
	}
	return -1;
}

int split(string a[], int n, string splitter) {
	if (n < 0) return -1;
	quickSort(a, n, splitter, 0, n - 1);	//sort the array
	for (int i = 0; i < n; i++) {
		if (a[i] >= splitter) return i;	//if sorted array has a element that equal or bigger than splitter, return its index
	}
	return n;	//if no elements equal or bigger than splitter, return n
}

void quickSort(string a[], int n, string target, int left, int right) {
	if (left < right) {
		int index = partition(a, left, right);	//get the index that already sorted
		quickSort(a, n, target, left, index - 1);	//sort the left part
		quickSort(a, n, target, index + 1, right);	//sort the right part
	}
}

int partition(string a[], int left, int right) {
	int pivot = left;	//choose a pivot
	int index = left + 1;
	int curr = index;
	while (curr <= right) {
		if (a[curr] < a[pivot]) {
			swap(a, index, curr);	//if current elements less than pivot one, swap two elements between index and curr
			index++;	//move the index to next position
		}
		curr++;
	}
	swap(a, pivot, index - 1);	//set the pivot to right position
	return index - 1;
}

void swap(string a[], int i, int j) {
	string temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void testAppendToAll() {
	string people[5] = { "boris", "gordon", "rishi", "liz", "john" };
	assert(appendToAll(people, 5, "!!!") == 5);
	// now people[0] is "boris!!!", people[1] is "gordon!!!", ...,
	// and people[4] is "john!!!"

	string a[] = { "dianne", "fiona", "ed", "xavier", "greg" };
	assert(appendToAll(a, 2, "!!!") == 2 && a[0] == "dianne!!!" && a[1] == "fiona!!!" && a[2] == "ed" && a[3] == "xavier" && a[4] == "greg");
	//test for a valid input
	assert(appendToAll(a, 4, "!!!") == 4 && a[0] == "dianne!!!!!!" && a[2] == "ed!!!" && a[3] == "xavier!!!" && a[4] == "greg");
	//test for a more positions
	assert(appendToAll(a, 5, "!!!") == 5 && a[4] == "greg!!!");
	//test all positions
	assert(appendToAll(a, -1, "!!!") == -1);
	//test for an invalid index

	string b[] = { "dianne", "fiona", "ed", "xavier", "greg", ""};
	assert(appendToAll(b, 0, "!!!") == 0 && b[0] == "dianne");
	//test 0 elements in array
	assert(appendToAll(b, 6, "") == 6);
	//test for adding an empty string
	assert(appendToAll(b, 6, " win!") == 6 && b[0] == "dianne win!" && b[5] == " win!");
	//test for another string
}

void testLookup() {
	string names[6] = { "david", "liz", "margaret", "tony", "gordon", "boris" };
	assert(lookup(names, 6, "david") == 0);	//return 0
	assert(lookup(names, 6, "boris") == 5);	//return 5
	assert(lookup(names, 5, "boris") == -1);	//return -1
	assert(lookup(names, 5, "tony") == 3);	//return 3

	string a[6] = {"A", "b", "c", "d", "E", ""};
	assert(lookup(a, 6, "E") == 4);
	//test for a valid input
	assert(lookup(a, 6, "e") == -1);
	//test for case sensitive
	assert(lookup(a, 3, "e") == -1);
	//test if the n variable works
	assert(lookup(a, 6, "G") == -1);
	//test if there is no such string
	assert(lookup(a, 6, "") == 5);
	//test for empty string
	assert(lookup(a, -1, "e") == -1);
	//test for a invalid position
	assert(lookup(a, 0, "e") == -1);
}

void testPositionOfMax() {
	string pm[6] = { "david", "liz", "margaret", "tony", "gordon", "boris" };
										   // in alphabetic order
	assert(positionOfMax(pm, 6) == 3);   // returns 3, since  tony  is latest

	string a[8] = { "Xander","bob", "Bob", "cabbage", "cabbage","Alice", "coco", ""};

	assert(positionOfMax(a, 8) == 6);
	assert(positionOfMax(a, 6) == 3);
	assert(positionOfMax(a, 5) == 3);
	assert(positionOfMax(a, 3) == 1);
	assert(positionOfMax(a, 1) == 0);	//test for only one element
	assert(positionOfMax(a, 0) == -1);	//test for no interesting elements
	assert(positionOfMax(a, -1) == -1);	//test for negative position
}

void testRotateLeft() {
	string mp[5] = { "john", "david", "liz", "theresa", "margaret" };
		// mp now contains:  "john", "liz", "theresa", "margaret", "david"
	assert(rotateLeft(mp, 5, 1) == 1);   // returns 1

	string a[5] = { "kevin", "jack", "bob", "alice", "" };
	assert(rotateLeft(a, 5, 1) == 1 && a[1] == "bob" && a[2] == "alice" && a[3] == "" && a[4] == "jack");
	//test one valid input
	assert(rotateLeft(a, 0, 3) == -1);
	//test an invalid pos
	assert(rotateLeft(a, 4, 4) == -1);
	//test an edge case for an invalid pos
	assert(rotateLeft(a, 0, 0) == -1);
	//test both two variables are 0
	assert(rotateLeft(a, 0, 3) == -1);
	//test no interesting element in array
	assert(rotateLeft(a, -4, 1) == -1);
	//test invalid n
	assert(rotateLeft(a, 5, -4) == -1);
	//test invalid pos
	assert(rotateLeft(a, 5, 6) == -1);
	//test the pos exceed n

	string b[6] = { "This", "is", "a", "test", "case", "!" };
	assert(rotateLeft(b, 6, 5) == 5 && b[5] == "!");
	//no rotate
	assert(rotateLeft(b, 4, 2) == 2 && b[2] == "test" && b[3] == "a");
	//test for a partially rotate

	string c[3] = { "A", "B", "C" };
	assert(rotateLeft(c, 3, 0) == 0 && c[0] == "B" && c[2] == "A");
};

void testCountRuns() {
	string d[9] = {"tony", "boris", "rishi", "rishi", "gordon", "gordon", "gordon", "rishi", "rishi"};
		   //  The five sequences of consecutive identical items are
		   //    "tony"
		   //    "boris"
		   //    "rishi", "rishi"
		   //    "gordon", "gordon", "gordon"
		   //    "rishi", "rishi"
	assert(countRuns(d, 9) == 5);   //  returns 5

	string a[6] = {"A","A","a","a","A","A"};
	assert(countRuns(a, 6) == 3);
	//test valid input
	assert(countRuns(a, 5) == 3);
	//test for another n
	assert(countRuns(a, 4) == 2);
	//test for another n with different runs
	assert(countRuns(a, 2) == 1);
	//test for another n with different runs
	assert(countRuns(a, 0) == 0);
	//test 0 as input
	assert(countRuns(a, -3) == -1);
	//test bad input
	
	string b[10] = { "A", "", "", "b", "b", "b", "b", "", "", "K" };
	assert(countRuns(b, 10) == 5);
	//test for empty string
	assert(countRuns(b, 5) == 3);
	//test for another n
}

void testFlip() {
	string leader[6] = { "boris", "rishi", "", "tony", "theresa", "david" };
		// leader now contains:  "tony"  ""  "rishi"  "boris"  "theresa"  "david"
	assert(flip(leader, 4) == 4);  // returns 4

	string a[6] = {"alice", "bob", "coco", "dot", "eye", ""};
	assert(flip(a, -3) == -1);
	//test for invalid n
	assert(flip(a, 0) == 0);
	//test for 0 as n
	assert(flip(a, 3) == 3 && a[0] == "coco" && a[1] == "bob" && a[2] == "alice" && a[3] == "dot");
	//test a partial flip
	assert(flip(a, 6) == 6 && a[0] == "" && a[1] == "eye" && a[2] == "dot" && a[3] == "alice" && a[4] == "bob" && a[5] == "coco");
	//test a total flip
}

void testDiffer() {
	string leader[6] = { "boris", "rishi", "", "tony", "theresa", "david" };
	string politician[5] = { "boris", "rishi", "david", "", "tony" };
	assert(differ(leader, 6, politician, 5) == 2);  //  returns 2
	assert(differ(leader, 2, politician, 1) == 1);  //  returns 1


	string a[8] = { "a","b","c","d","e","f","g","h" };
	string b[6] = { "a","b","c","d","e","f" };
	string c[6] = { "a","","c","d","e","f" };
	string copy[8] = { "a","b","c","d","e","f","g","h" };


	assert(differ(a, -2, b, 3) == -1);
	//test invalid n for first array
	assert(differ(a, 8, b, -3) == -1);
	//test invalid n for second array
	assert(differ(a, 0, b, 3) == 0);
	//test for 0 as n in first array
	assert(differ(a, 3, b, 0) == 0);
	//test for 0 as n in second array
	
	assert(differ(a, 8, b, 6) == 6);
	//test elements are equal, but a is longer than b
	assert(differ(b, 6, c, 6) == 1);
	//test two different array with same length
	assert(differ(a, 8, c, 6) == 1);
	//test two different array with different length
	assert(differ(a, 8, copy, 8) == 8);
	//test two exactlly same array

	assert(differ(a, 0, b, 0) == 0);
	//test for both n are 0
}

void testSubsequence() {
	string names[10] = { "john", "margaret", "theresa", "rishi", "boris", "liz" };
	string names1[10] = { "margaret", "theresa", "rishi" };
	assert(subsequence(names, 6, names1, 3) == 1);  // returns 1
	string names2[10] = { "john", "rishi" };
	assert(subsequence(names, 5, names2, 2) == -1);  // returns -1

	string a[10] = { "a", "b", "c", "d", "e", "e", "f", "g", "h", "" };
	string copy[10] = { "a", "b", "c", "d", "e", "e", "f", "g", "h", "" };
	string b[3] = { "a", "b", "c" };
	string c[4] = { "c", "d", "e", "e" };
	string d[3] = { "g", "h", "" };
	string e[1] = { "e" };
	string f[1] = { "" };
	string g[2] = {"", ""};
	string h[2] = { "e", "e" };
	string i[3] = { "e", "f", "g" };

	assert(subsequence(a, 10, copy, 10) == 0);
	//test if two array totally equal
	assert(subsequence(a, 10, copy, 3) == 0);
	//test partial of copy
	assert(subsequence(a, 10, b, 3) == 0);
	//test a valid input in the begining
	assert(subsequence(a, 5, copy, 10) == -1);
	//test the second array is longer than first one
	assert(subsequence(a, 10, c, 4) == 2);
	//test a valid input in the middle
	assert(subsequence(a, 10, d, 3) == 7);
	//test a valid input in the end
	assert(subsequence(a, 10, e, 1) == 4);
	//test a valid input in the middle
	assert(subsequence(a, 10, f, 1) == 9);
	//test an empty input
	assert(subsequence(a, 10, copy, 0) == 0);
	//test a sequence of 0 elements
	assert(subsequence(a, 10, g, 2) == -1);
	//test an array that not in the first array
	assert(subsequence(a, 10, h, 2) == 4);
	//test a valid input
	assert(subsequence(a, 6, h, 2) == 4);
	//test a valid input with partial of first array
	assert(subsequence(a, 5, h, 2) == -1);
	//test an edge case with partial of first array
	assert(subsequence(a, 5, h, 1) == 4);
	//test a valid input with partial of first array
	assert(subsequence(a, 10, i, 3) == 5);
	//test two consective elements that only one in the second array

	assert(subsequence(a, 3, i, 0) == 0);
	assert(subsequence(a, 0, i, 0) == 0);
	//return 0 if two sequence are 0
	assert(subsequence(a, 0, i, 1) == -1);
	//return -1 if the first sequence is 0 but the second one is not 0


	string j[10] = {"John","Kevin", "Kevin","Kevin","Xander","","Bob","Bob","Bob","Bob"};
	string k[5] = { "Kevin","Kevin","Xander","","Bob" };
	string l[5] = { "Kevin", "Xander","", "Bob", "Bob"};
	string m[3] = { "Bob", "Bob", "Bob" };
	string n[4] = { "Bob","Bob","Bob","Bob" };
	//tests for repeated elements
	assert(subsequence(j, 10, k, 5) == 2);
	assert(subsequence(j, 10, l, 4) == 3);
	assert(subsequence(j, 10, m, 3) == 6);
	assert(subsequence(j, 10, n, 4) == 6);

}

void testLookupAny() {
	string names[10] = { "john", "margaret", "theresa", "rishi", "boris", "liz" };
	string set1[10] = { "david", "boris", "rishi", "margaret" };
	assert( lookupAny(names, 6, set1, 4) == 1 );  // returns 1 (a1 has "margaret" there)
	string set2[10] = { "tony", "gordon" };
	assert( lookupAny(names, 6, set2, 2) == -1 );   // returns -1 (a1 has none)
	                              
	string a[10] = { "a", "b", "c", "d", "e", "e", "f", "g", "h", "" };
	string b[3] = {"x", "y", "z"};
	string c[3] = { "A", "B", "C" };
	string d[3] = {"A", "", "B"};
	string e[1] = { "e" };
	string f[3] = {"b", "a", "c"};

	assert(lookupAny(a, 10, b, 3) == -1);
	//test an invalid input
	assert(lookupAny(a, 10, c, 3) == -1);
	//test case sensitive
	assert(lookupAny(a, 10, d, 3) == 9);
	//test lookup an empty string
	assert(lookupAny(a, 10, e, 1) == 4);
	//test multiple target string in first array
	assert(lookupAny(a, 10, f, 3) == 0);
	//test if multiple target string in second array
	assert(lookupAny(a, 3, f, 3) == 0);
	//test partial of first array
	assert(lookupAny(a, 3, f, 2) == 0);
	//test partial of second array which is valid
	assert(lookupAny(a, 1, f, 1) == -1);
	//test partial of second array which is not valid

	assert(lookupAny(a, -2, f, 1) == -1);
	//test invalid n1
	assert(lookupAny(a, 10, f, -2) == -1);
	//test invalid n2

	assert(lookupAny(a, 10, f, 0) == -1);
	//test if the second array contains 0 elements
	assert(lookupAny(a, 0, f, 1) == -1);
	//test if the first array contains 0 elements
}

void testSplit() {
	string pm[6] = { "david", "liz", "margaret", "tony", "gordon", "boris" };
	assert(split(pm, 6, "john") == 3);  //  returns 3
		// pm must now be
		//      "david"  "gordon"  "boris"  "liz"  "tony"  "margaret"
		// or   "gordon"  "boris"  "david"  "margaret"  "liz"  "tony"
		// or one of several other orderings.
		// All elements < "john" (i.e., "gordon", "boris", and "david")
		//   come before all others
		// All elements > "john" (i.e., "tony", "liz", and "margaret")
		//   come after all others
	string pm2[4] = { "margaret", "theresa", "liz", "rishi" };
	assert(split(pm2, 4, "rishi") == 2);  //  returns 2
		// pm2 must now be either
		//      "margaret"  "liz"  "rishi"  "theresa"
		// or   "liz"  "margaret"  "rishi"  "theresa"
		// All elements < "rishi" (i.e., "liz" and "margaret") come
			// before all others.
		// All elements > "rishi" (i.e., "theresa") come after all others.

	string a[10] = {"","Alice","BoB","xander","OK","magic","sun","possible", "Alice", "final"};
	assert(split(a, 10, "") == 0);
	//test for split by an empty string
	assert(split(a, 10, "Alice") == 1);
	//test for multiple targets
	assert(split(a, 7, "Alice") == 1);
	//test for partial of the array
	assert(split(a, 3, "final") == 3);
	//test for a string that not in the range of n
	assert(split(a, 10, "BoBA") == 4);
	//test for a nonexist string
	assert(split(a, -3, "check") == -1);
	//test a bad input

	string b[3] = { "d","A","a" };

	assert(split(b, 3, "e") == 3);
	//test a string bigger than all strings
	assert(split(b, 3, "c") == 2);
	//test a string bigger than 2 strings 
	assert(split(b, 3, "E") == 1);
	//test a string bigger than 1 string
	assert(split(b, 3, "") == 0);
	//test an empty input

	assert(split(b, 3, "A") == 0);
	//test the first string in order of alphabet
	assert(split(b, 3, "a") == 1);
	//test the second string in order of alphabet
	assert(split(b, 3, "d") == 2);
	//test the third string in order of alphabet
	assert(split(b, 0, "a") == 0);
	//test the case that n equals 0
}

void print(string a[], int n) {
	for (int i = 0; i < n; i++) cout << a[i] << endl;
}

int main() {
	testAppendToAll();
	testLookup();
	testPositionOfMax();
	testRotateLeft();
	testCountRuns();
	testFlip();
	testDiffer();
	testSubsequence();
	testLookupAny();
	testSplit();
	cerr << "All test cases passed." << endl;
}
