#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct wordStruct {
    string word;
    double value = 0;
};

int readSentimentFile(vector<wordStruct>& wordList, vector<wordStruct>& posList, vector<wordStruct>& negList);
//PRE: vectors are empty
//POST: read sentiment.txt and load vectors

int processReview(string fileName, vector<wordStruct> wordList, vector<wordStruct> posList, vector<wordStruct> negList);
//PRE: vectors are empty
//POST: read sentiment.txt and load vectors


int binarySearch(string str, vector<wordStruct> wordList, int high, int low);
//PRE: takes in word from review vector
//POST: returns said word's index if it exists in the list of all words and their sentiments (sentiment.txt)