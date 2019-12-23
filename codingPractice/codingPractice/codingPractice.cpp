// codingPractice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>

using namespace std;

string translateWord(const string& word) {
	string newStr = NULL;
	for (int i = 0; i < word.length(); ++i) {
		if (isalpha(word[i])) newStr += tolower(word[i]);
	}
	return newStr;
}

vector<vector<string>> wordCountEngine(const string& document)
{
	// your code goes here
	list<pair<string, int>> myList;
	unordered_map<string, list<pair<string,int>>::iterator> wordCtrMap;

	vector<vector<string>> outStringVec;
	string currWord = NULL;
	int max_ctr = 0;

	for (int i = 0; i < document.length(); ++i) {
		if (document[i] == ' ' || document[i] == '\n') {
			if (!currWord.empty()) {
				string temp = translateWord(currWord);
				if (!wordCtrMap.count(temp)) {
					myList.push_back(make_pair(temp, 1));
					auto it = myList.end(); it--;
					wordCtrMap[temp] = it;
				}
				else
				{
					wordCtrMap[temp]->second++;
				}
				
				if (max_ctr < wordCtrMap[temp]->second) max_ctr = wordCtrMap[temp]->second;
				currWord.clear();
			}
		}
		else  currWord += document[i];

	}
	vector<vector<string>> sortedStrVec(max_ctr);


	for (auto it = myList.begin(); it != myList.end(); ++it) {
		cout << it->first << ":" << to_string(it->second) << endl;
		sortedStrVec[it->second].push_back(it->first);
	}

	for (int i = sortedStrVec.size() - 1; i > 0; --i) {
		for (int j = 0; j < sortedStrVec[i].size(); ++j)
			outStringVec.push_back({ sortedStrVec[i][j], to_string(i) });
	}

	return outStringVec;


}
int main() {

	string inStr;
	cout
		<< "Input String here: " << endl;
	cin >> inStr;

	auto myVec = wordCountEngine(inStr);
	return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
