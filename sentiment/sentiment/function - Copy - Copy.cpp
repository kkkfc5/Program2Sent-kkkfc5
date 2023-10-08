#pragma once
#include "function.h"

int iter = 0; // global var for iteration


int readSentimentFile(vector<wordStruct>& wordList, vector<wordStruct>& posList, vector<wordStruct>& negList) {

    ifstream inFile;
    inFile.open("sentiment.txt");
    if (!inFile.is_open()) {
        cout << "Unable to open file\n";
        return -1;
    }

    wordStruct tempWord;
    vector<string> row;
    string inRec, tempString;

    getline(inFile, inRec); // read record from file
    while (inFile.good()) {
        stringstream inSS(inRec); // create string stream
        row.clear();
        while (getline(inSS, tempString, ',')) { // separate stringstream on ,
            row.push_back(tempString);             // push each onto a string vector
        }

        tempWord.word = row[0];        // row[0] = word
        tempWord.value = stod(row[1]); // row[1] = value  add try catch
        wordList.push_back(tempWord);  // push word & value onto wordList
        if (tempWord.value > 1.25)
            posList.push_back(tempWord);
        else if (tempWord.value < -1.25)
            negList.push_back(tempWord);

        getline(inFile, inRec); // get next input record
    }
    /*/
    for(auto i : posList) {
        cout << i.word << " ";
    }
    cout << "\n\n\n\n\n\n=============================\nsize of : " << sizeof(posList)  << "\n" << posList.size() << "\n=============================\n\n\n\n\n\n";
    */
    inFile.close();
    return 0;
}




//===========================================================================================================================
//===========================================================================================================================
//===========================================================================================================================
//===========================================================================================================================
//===========================================================================================================================




void outputFile(double totalSentiment, vector<wordStruct> formattedTextFile, int& iter) {
    ofstream outFile;
    if (iter == 0) { // if the first iteration
        outFile.open("reviewsPart1.txt"); // purge the contents of reviewsPart1.txt
        iter++;

        cout << "\n\n FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST ";
        cout << "\n\n FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST ";
        cout << "\n\n FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST ";
        cout << "\n\n FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST ";
        cout << "\n\n FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST ";
    }
    else {
        outFile.open("reviewsPart1.txt", ios::app); // opns file in append mode
    }

    cout << "ORIGINAL SENTIMENT: " << totalSentiment << endl;
    outFile << "ORIGINAL SENTIMENT: " << totalSentiment << "\n\n";

    cout << "FORMATTED REVIEW: \n";
    outFile << "FORMATTED REVIEW: \n";
    for (auto i : formattedTextFile) {
        cout << i.word << " ";
        outFile << i.word << " ";
    }

    outFile << "\n\n\n\n";

    outFile.close();
    return;
}




wordStruct replace(vector<wordStruct>& textFile, int index, vector<wordStruct> posList, vector<wordStruct> negList) {
    wordStruct currentWord = textFile[index];

    int replaceIndex;


    if (currentWord.value > 1.25) {
        // find poslist word to replace with
        replaceIndex = rand() % negList.size() * 100;
        cout << "\n\n\n\n\n/////////////////////////////\nreplace index: " << replaceIndex << "\n/////////////////////////////\n\n\n\n\n";
        textFile[index].word = negList[replaceIndex].word;
        textFile[index].value = negList[replaceIndex].value; // replaces value as well

        //cout << "made more negative! : "
    }
    else if (currentWord.value < -1.25) {
        // find neglist word to replace it with
        replaceIndex = rand() % (posList.size()) * 100;
        cout << "\n\n\n\n\n/////////////////////////////\nreplace index: " << replaceIndex << "\n/////////////////////////////\n\n\n\n\n";
        textFile[index].word = posList[replaceIndex].word;
        textFile[index].value = posList[replaceIndex].value;
    }


    return currentWord;
}



// helper functions above -----------------------------------------------------------


















int processReview(string fileName, vector<wordStruct> wordList, vector<wordStruct> posList, vector<wordStruct> negList) {
    ifstream inFile;
    inFile.open(fileName);
    if (!inFile.is_open()) {
        cout << "Review file: " << fileName << " invalid\n";
        return -1;
    }

    double currentSent = 0; // for the current sent
    double totalSentiment = 0; // for total sent
    string str1;
    vector<wordStruct> formattedTextFile;


    while (inFile >> str1) { // while you can still receive words from file
        // cout << str1; ADD "IF STR1 != , OR ! OR ? OR . THEN PRINT SPACE AFTER WORD"
        // if st[-1] == punctuation, then add that punct to a temp char, add it back once changed word to pos/neg
        string editStr1 = str1;
        wordStruct currentWord;

        for (int i = 0; i < str1.length(); i++) {

            // if alpha, go lowercase
            if (isalpha(str1[i])) {
                editStr1[i] = tolower(str1[i]);
            }
        }

        char tempPunct = editStr1[editStr1.size() - 1];
        bool wordHasPunct = false;



        //if editstr has punctuation
        if (ispunct(tempPunct) || !isalpha(tempPunct) && !isdigit(tempPunct)) {
            cout << "THE PUNCTUATION IS  " << tempPunct << "";
            cout << "\neditstring1 is :  >>   " << editStr1;
            editStr1.erase(editStr1.end() - 1);
            cout << "\neditstring1 is :  >>   " << editStr1 << endl << endl;
            wordHasPunct = true;
        }






        currentSent = originalSentiment(editStr1, wordList); // becasue we need to add the singular words' value to a struct, we have return value by itself to a variable
        totalSentiment += currentSent;

        if (wordHasPunct) {
            editStr1 += tempPunct; // fixes editstr1 to original state with it's punctuation
            wordHasPunct = false;
        }


        currentWord.word = editStr1;
        currentWord.value = currentSent;

        formattedTextFile.push_back(currentWord);

    } // end while 




    replace(formattedTextFile, 0, posList, negList);
    // CALL OUTPUT FUNC  
    outputFile(totalSentiment, formattedTextFile, iter); // passes in the iteration var that's needed




    //find value of lowercase string if positive make it neg, vice versa
         // if pos, put rand word in neg vector with its value too
        // else, put original in new vector



    inFile.close();
    return 0;
}




// going to add what is returned to a double holding the sentiment value
double originalSentiment(string str, vector<wordStruct>& wordList) {
    if (isalpha(str[0])) { // if the string is a word
        //search for str in wordlist, take its index, take index and find the value, add value to total
        int index = binarySearch(str, wordList, wordList.size(), 0, 1); // finds index of word
        if (index != -1.0) { // IF BINARY SEARCH DOESNT FAIL
            //cout << "\n\n------------------\nvalue :  | " << wordList[index].value<< endl<< endl;
            return wordList[index].value;
        }
        //cout << "\nindex : | " << index;
    }
    return 0;
}


// == BINARY SEARCH BASED OFF THE ITERATIVE VERSION MODELED BY GEEKSFORGEEKS.COM == 
int binarySearch(string str, vector<wordStruct> wordList, int high, int low, int ite) {
    while (low <= high) {
        /*
        cout << "\n - - - :: >> " << ite << " << :: - - - \n"; // since this isn't ++ing, the problem is that it loops over and over in the while loop. thus the problem is the conditions recursive calling
        ite = ite + 1;
        cout << "high: " << high << "\n low: " << low;
        */

        int mid = low + (high - low) / 2;
        //cout << "\n mid: " << mid << " (wordlist at mid: " << wordList[mid].word << " whilst str is: " << str << " )";

        if (wordList[mid].word == str) { // if the wordlist at mid index equals the string,
            return mid; // returns mid index 
        }
        if (wordList[mid].word < str) {
            low = mid + 1;
        }
        else high = mid - 1;
    }

    return -1; // if base case :: ie, if not in list
}