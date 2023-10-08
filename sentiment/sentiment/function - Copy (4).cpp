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






// 
void outputFile(double totalSentiment, vector<wordStruct> originalTextFile, int& iter) {
    ofstream outFile;
    if (iter == 0) { // if the first iteration
        outFile.open("reviewsPart1.txt"); // purge the contents of reviewsPart1.txt
        iter++;

        cout << "\n\n FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST ";
        cout << "\n\n FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST ";
        cout << "\n\n FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST ";
        cout << "\n\n FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST ";
        cout << "\n\n FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST FIRST \n\n";
    }
    else {
        outFile.open("reviewsPart1.txt", ios::app); // opns file in append mode
    }

    cout << "ORIGINAL SENTIMENT: " << totalSentiment << endl << "\n";
    outFile << "ORIGINAL SENTIMENT: " << totalSentiment << "\n\n";

    cout << "FORMATTED REVIEW: \n";
    outFile << "FORMATTED REVIEW: \n";
    for (auto i : originalTextFile) {
        cout << i.word << " ";
        outFile << i.word << " ";
    }

    outFile << "\n\n\n\n";

    outFile.close();
    return;
}




void replace(vector<wordStruct>& textFile, int formattedIndex, vector<wordStruct> posList, vector<wordStruct> negList) {
    wordStruct currentWord = textFile[formattedIndex];
    

    int replaceIndex; // rand index for replacing words


    if (currentWord.value > 1.25) {
        // find poslist word to replace with
        replaceIndex = rand() % negList.size();

        cout << "\n\n\n replacement index: " << replaceIndex << "\nsize of poslist: " << negList.size();

        cout << "\n[[[[[[[[[[[[[[[[[[[[[[[[[\nReplacement word AAA: ";
        cout << negList[replaceIndex].word << " " << negList[replaceIndex].value;
        cout << "\n\nOriginal word: ";
        cout << textFile[formattedIndex].word << " " << textFile[formattedIndex].value << "\n]]]]]]]]]]]]]]]]]]]]]]]]]\n";
        cout << "======  formatted index: " << formattedIndex << "  ======\n";
        cout << "======   replace index: " << replaceIndex << "   ======\n\n\n\n";

        textFile[formattedIndex].word = negList[replaceIndex].word;
        textFile[formattedIndex].value = negList[replaceIndex].value; // replaces value as well



        //cout << "made more negative! : "
    }
    else if (currentWord.value < -1.25) {
        // find neglist word to replace it with
        replaceIndex = rand() % posList.size();

        //MAKE COUT INTO MULTIPLE LINES SO WE CAN SEE EXACTALLY WHERE IT ERRORS
        cout << "\n\n\n\n[[[[[[[[[[[[[[[[[[[[[[[[[\nReplacement word BBB: "; 
        cout << posList[replaceIndex].word << " " << posList[replaceIndex].value;
        cout << "\n\nOriginal word: "; 
        cout << textFile[formattedIndex].word << " " << textFile[formattedIndex].value << "\n]]]]]]]]]]]]]]]]]]]]]]]]]\n";
        cout << "======  formatted index: " << formattedIndex << "  ======\n";
        cout << "======   replace index: " << replaceIndex << "   ======\n\n\n\n";
        

        textFile[formattedIndex].word = posList[replaceIndex].word;
        textFile[formattedIndex].value = posList[replaceIndex].value;
    }


    return;
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
    vector<wordStruct> formattedTextFile, originalTextFile;
    int index = 0;
    int formattedIndex = 0;
    vector<int> replaceIndex;

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
            //cout << "THE PUNCTUATION IS  " << tempPunct << "";
            //cout << "\neditstring1 is :  >>   " << editStr1;
            editStr1.erase(editStr1.end() - 1);
            //cout << "\neditstring1 is :  >>   " << editStr1 << endl << endl;
            wordHasPunct = true;
        }


        if (isalpha(editStr1[0])) { // if the string is a word
            index = binarySearch(editStr1, wordList, wordList.size(), 0, 1); // finds index of word
            if (index != -1.0) { // IF BINARY SEARCH DOESNT FAIL
                cout << "\n++++++++++ : value :  " << wordList[index].value
                     << "\n++++++++++ : word  :  " << wordList[index].word << "\n\n\n";
                replaceIndex.push_back(index);
                totalSentiment += wordList[index].value;
            }
            //currentSent = originalSentiment(editStr1, wordList); // becasue we need to add the singular words' value to a struct, we have return value by itself to a variable
            //totalSentiment += wordList[index].value;
        }


        if (wordHasPunct) {
            editStr1 += tempPunct; // fixes editstr1 to original state with it's punctuation
            wordHasPunct = false;
        }


        currentWord.word = editStr1;
        currentWord.value = wordList[formattedIndex].value;


        formattedTextFile.push_back(currentWord); // sets the formatted text file = text that is lowercase but otherwise untouched
        originalTextFile.push_back(currentWord);
        replace(formattedTextFile, formattedIndex, posList, negList);
        formattedIndex++;
    } // end while 



    // CALL OUTPUT FUNC  
    //outputFile(totalSentiment, originalTextFile, iter); // passes in the iteration var that's needed
    
    for (auto i : originalTextFile) {
        cout << i.word << " ";
    }

    cout << "\n\nedited: \n";
    for (auto i : formattedTextFile) {
        cout << i.word << " ";
    }



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