#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 6262)
#include "utilities.h"
#include <iostream>
#include <cstring>
#include <climits>

using namespace std;
int playOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum);
void judgeWord(char[], char[]);
bool isValidInput(char[]);
bool containsWord(const char words[][MAXWORDLEN + 1], char word[MAXWORDLEN + 1], int nWords);

void printStatus(int, int);
void printInvalidInput();
void printResult(int, int, int, int, int);
void printNotContains();
void printNotLoaded();

const int MAX_WORDS = 100000, GUESS_LEN = 1000;
const char wordfilename[] = "C:/Users/zhang/Documents/Github/CS31/Project5/Project5/mywordfile.txt";
 
int main() {
	char wordList[MAX_WORDS][MAXWORDLEN + 1];
	int nWords = getWords(wordList, MAX_WORDS, wordfilename);
	if (nWords <= 0) {
		printNotLoaded();
		return -1;	//NOT SURE
	}
	int playRounds, totalScore = 0, minScore = INT_MAX, maxScore = INT_MIN;
	cout << "How many rounds do you want to play? ";
	cin >> playRounds;
	cin.ignore(10000, '\n');
	for (int round = 1; round <= playRounds; round++) {
		cout << endl;
		cout << "Round " << round << endl;
		int rdm = randInt(0, nWords - 1);
		int score = playOneRound(wordList, nWords, rdm);
 		minScore = minScore > score ? score : minScore;	//record the min score
		maxScore = maxScore < score ? score : maxScore;	//record the max score
		totalScore += score;	//record the total score
		printResult(score, totalScore, round, minScore, maxScore);	//print result at the end of each round
	}
}

int playOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum) {
	if (nWords <= 0 || wordnum < 0 || wordnum >= nWords) return -1;

	int score = 1;
	char answer[MAXWORDLEN + 1];
	strcpy(answer, words[wordnum]);
	char guess[GUESS_LEN];
	//cout << answer << endl;	//test use
	cout << "The hidden word is " << strlen(answer) << " letters long." << endl;
	for (;;) {	//loop it until we got our answer
		cout << "Probe word: ";
		//
		cin.getline(guess, 1000);
		//cin >> guess;
		if (!isValidInput(guess)) printInvalidInput();	//print invalid input warning if guess is not valid
		else if (!containsWord(words, guess, nWords)) printNotContains();	//print warning if words don't contains that word
		else if (strcmp(guess, answer)) {	//if we don't hit the answer, score plus one and call judgeWord() to count how many characters we hit
			score++;
			judgeWord(answer, guess);
		}
		else break;	//if we hit the answer, break
	}
	return score;
}

void judgeWord(char answer[], char guess[]) {
	int gold = 0, silver = 0;
	int bin1[26] = { 0 }, bin2[26] = { 0 };	//two bins to record characters from two words that not matched
	int answerLen = strlen(answer), guessLen = strlen(guess);

	for (int i = 0; i < answerLen; i++) {
		if (i < guessLen && answer[i] == guess[i]) gold++;	//if two characters are matched, gold plus 1
		else bin1[answer[i] - 'a']++;	//if not match, record it in bin1
	}

	for (int i = 0; i < guessLen; i++) {
		if (i < answerLen && answer[i] == guess[i]) continue;	//if two characters are matched, continue	
		else bin2[guess[i] - 'a']++;	//if not match, record it in bin2
	}

	for (int i = 0; i < 26; i++) {
		silver += bin1[i] < bin2[i] ? bin1[i] : bin2[i];	//count total silvers by adding up the number of characters that bin1 and bin2 both contains 
	}
	printStatus(gold, silver);	//print the numbers of golds and silvers
}

bool isValidInput(char guess[]) {
	if (strlen(guess) < MINWORDLEN || strlen(guess) > MAXWORDLEN) return false;
	int k = strlen(guess);
	for (int i = 0; i < k; i++) {
		if (!islower(guess[i])) return false;
	}
	return true;
}

bool containsWord(const char words[][MAXWORDLEN + 1], char word[MAXWORDLEN + 1], int nWords) {
	for (int i = 0; i < nWords; i++) {
		if (!strcmp(words[i], word)) return true;
	}
	return false;
}

void printStatus(int gold, int silver) {
	cout << "Golds: " << gold << ", Silvers: " << silver << endl;
}

void printInvalidInput() {
	cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
}

void printResult(int score, int totalScore, int round, int min, int max) {
	if (score == 1) cout << "You got it in " << score << " try." << endl;
	else cout << "You got it in " << score << " tries." << endl;
	std::cout << std::fixed;	//NOT Sure
	cout.precision(2);
	double average = (totalScore * 1.0) / round;
	cout << "Average: " << average << ", minimum: " << min << ", maximum: " << max << endl;
}

void printNotContains() {
	cout << "I don't know that word." << endl;
}

void printNotLoaded() {
	cout << "No words were loaded, so I can't play the game." << endl;
}