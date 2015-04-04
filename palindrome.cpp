#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>
#include <vector>
#include <algorithm>
#include "merge.h"

using namespace std;

int main (int argc, char* argv[])
{
    string input;
    string line;
    int sentencecount=0;
    int success = 0;
    unsigned int j;
    int x;
	int found;

    string buf;
    vector<string> word; //to store each word of each sentence

    string temp_palin; //to store words to be concatenated to palindrome
    vector<string> palin;//to store all palindromes (master list)
    vector<string> s_palin;// to store palindromes from each sentence

    //quit if there are too many arguments
    if (argc != 2) {
    	return 0;
    }

    //input file name
    input = argv[1];

    //go through file line by line
    ifstream myfile (input.c_str());
    assert(myfile.is_open());

    //this is the first line of the file
    getline (myfile,line);
    sentencecount++;

    //split the line by space
	stringstream ss(line);
	while (ss>>buf) {
		word.push_back(buf);
	}

	//look for all possible palindromes
	unsigned int upper_odd;
	int lower_odd;
	unsigned int upper_even;
	int lower_even;

	//odd number of words in palindrome
	for (j=1; j<word.size();j++) {
		upper_odd = j+1;
		lower_odd = j-1;
		lower_even = j-1;
		upper_even = j;

		temp_palin.clear();
		//as long as this condition is met, it is a palindrome
		//longer palindromes will also meet condition
		if ((lower_even >= 0 && upper_even < word.size()) && (word[upper_odd] == word[lower_odd])){
		while ((lower_odd >= 0 && upper_odd < word.size()) &&
				(word[lower_odd] == word[upper_odd]) ){

			temp_palin.clear();
			for (x = lower_odd; x <= upper_odd; x++){
				temp_palin += word[x] + " ";
			}
			temp_palin.erase(temp_palin.end()-1); // remove last space

			//now add to vector to keep track of all palindromes
			palin.push_back(temp_palin);

			lower_odd--;
			upper_odd++;
		}
		}
		//even number of words in palindrome
		else if((lower_even >= 0 && upper_even < word.size()) && (word[lower_even] == word[upper_even])){
			temp_palin.clear();
			while ((lower_even >= 0 && upper_even < word.size()) &&
					word[lower_even] == word[upper_even]) {

				temp_palin.clear();
				for (x = lower_even; x <= upper_even; x++){
					temp_palin += word[x] + " ";
				}
				temp_palin.erase(temp_palin.end()-1); // remove last space

				//now add to vector to keep track of all palindromes
				palin.push_back(temp_palin);

				lower_even --;
				upper_even ++;
		}
		}
	}

	//Check if no palindromes in file
	if (palin.size() == 0) {
		return 0;
	}

	//At this point, palin has all palindromes from first sentence
	//Sort vector here
	mergesortstr (palin, 0, palin.size()-1);

	//palins now sorted longest to shortest
	myfile.close();

	int marker = 0;
	//check if all lines have the palindrome in sorted list
	while (marker < palin.size()) {

		ifstream myfilesec (input.c_str());
		getline(myfilesec,line); //ignore 1st sentence
		getline(myfilesec,line);

		//find largest palindrome in 2nd line 1st
		success = 0;
		for (j = marker; j < palin.size(); j++){
			found = line.find(palin.at(j));
			if (found!=std::string::npos){
				success = 1;
				marker = j;
				break;
			}
		}
		//went through all palindromes and no sentences matched
		//return at this point if no palins in list
		if (!success){
			return 0;
		}

		//check all other sentences
		while ( getline (myfilesec,line) )
		{
			found = line.find(palin.at(marker));
			if (found==std::string::npos){ //NOT found
				success = 0;
				break;
			}
			else {
				success = 1;
			}
			//marker has entry of palin that has longest palindrome

		}
		if (success) {
			myfilesec.close();
			break;
		}
		marker++;
		myfilesec.close();
	}

	//return nothing if no success
	if (!success){
		return 0;
	}

	cout << palin.at(marker) << endl;
	return 0;
}
