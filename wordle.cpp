// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void generateGuessSet(std::string in, std::string floating, std::set<std::string>& floatWords);
void generateRandomSet(std::string alphabet, std::string in, std::set<std::string>& randomWords);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
		std::set<std::string> guessWords;
		if (in.length() == 0) {
			return guessWords;
		}
		generateGuessSet(in, floating, guessWords);

		std::set<std::string> randomWords;
		string alphabet = "abcdefghijklmnopqrstuvwxyz";
		for (std::set<std::string>::iterator it = guessWords.begin(); it != guessWords.end(); ++it) {
			generateRandomSet(alphabet, (*it), randomWords);
		}
		std::set<std::string> hits;
		for (std::set<std::string>::iterator it = randomWords.begin(); it != randomWords.end(); ++it) {
			if (dict.find(*it) != dict.end()) {
				hits.insert(*it);
			}
		}
		return hits;
}

// Define any helper functions here
void generateGuessSet(std::string in, std::string floating, std::set<std::string>& floatWords) {
    //Should take in an input string (incomplete word with dashes), identify dashes, use floating letters to fill in the spaces. Add words to floatwords.
		//Use recursion to basically latch a letter into a dash and generate all combinations with this constraint.
		int inLength = in.length();
		

		if (floating.length() == 0) {
			floatWords.insert(in);
			return;
		}

		for (int i = 0; i < inLength; i++) { //for each letter in i…
			if (in[i] == '-') {//for each dash in input string, use floating letter and fill it in
				string temp = in;
				temp[i] = floating[0];
				generateGuessSet(temp,floating.substr(1),floatWords);
			}
		}
}

void generateRandomSet(std::string alphabet, std::string in, std::set<std::string>& randomWords) {
	//should use the randomset with any leftover dashes in the guessWords. If there are no empty spaces left, put the word in randomWords.
	if (in.find('-') == std::string::npos) {
		randomWords.insert(in);
		return;
	}

	unsigned int i = 0;
	while (i < in.length()) {
		if (in[i] == '-') {
			unsigned int j = 0;
			while (j < alphabet.length()) {
				string temp = in;
				temp[i] = alphabet[j];
				string tempAlphabet = alphabet;
				//size_t eraseLetter = tempAlphabet.find(alphabet[j]);
				//tempAlphabet.erase(tempAlphabet.begin() + eraseLetter); made runtime too long
				generateRandomSet(tempAlphabet.substr(j),temp,randomWords);
				j++;
			}
		}
		i++;
	}

}