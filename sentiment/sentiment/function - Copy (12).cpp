#pragma once
#include "function.h"

//int iter = 0; // global var for iteration


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
        if (tempWord.value > 1)
            posList.push_back(tempWord);
        else if (tempWord.value < -1)
            negList.push_back(tempWord);

        getline(inFile, inRec); // get next input record
    }
    
    inFile.close();
    return 0;
}




//===========================================================================================================================
//===========================================================================================================================
//===========================================================================================================================
//===========================================================================================================================
//===========================================================================================================================





// helper functions below -----------------------------------------------------------

/*

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




void replace(vector<wordStruct>& textFile, int formattedIndex, vector<wordStruct> posList, vector<wordStruct> negList, vector<int>& reviewReplaceIndex) {
    wordStruct currentWord = textFile[formattedIndex];
    //cout << "\n\nok so formatted index is :: :: :: :: :: (AKA LOOP ITERATION) :: :: :: :: ::  > > > > " << formattedIndex << "\n\n";

    int replaceIndex; // rand index for replacing words


    if (currentWord.value > 1) {
        // find poslist word to replace with
        replaceIndex = rand() % negList.size();

        //cout << "\n replacement index: " << replaceIndex << "\nsize of poslist: " << negList.size();

        cout << "\n[[[[[[[[[[[[[[[[[[[[[[[[[\nReplacement word AAA: ";
        cout << negList[replaceIndex].word << " " << negList[replaceIndex].value;
        cout << "\n\nOriginal word: ";
        cout << textFile[formattedIndex].word << " " << textFile[formattedIndex].value << "\n]]]]]]]]]]]]]]]]]]]]]]]]]\n";
        cout << "======  formatted index: " << formattedIndex << "  ======\n";
        cout << "======   replace index: " << replaceIndex << "   ======\n\n\n\n\n+_______________________________________________________\n";

        textFile[formattedIndex].word = negList[replaceIndex].word;
        textFile[formattedIndex].value = negList[replaceIndex].value; // replaces value as well


        reviewReplaceIndex.push_back(formattedIndex); // adds the index (aka the iteration of the while loop) of the replaced word in the review to the vector. used to print all the changed words at the end
        //cout << "made more negative! : "
    }
    else if (currentWord.value < -1) {
        // find neglist word to replace it with
        replaceIndex = rand() % posList.size();

        //MAKE COUT INTO MULTIPLE LINES SO WE CAN SEE EXACTALLY WHERE IT ERRORS
        cout << "\n\n\n\n[[[[[[[[[[[[[[[[[[[[[[[[[\nReplacement word BBB: "; 
        cout << posList[replaceIndex].word << " " << posList[replaceIndex].value;
        cout << "\n\nOriginal word: "; 
        cout << textFile[formattedIndex].word << " " << textFile[formattedIndex].value << "\n]]]]]]]]]]]]]]]]]]]]]]]]]\n";
        cout << "======  formatted index: " << formattedIndex << "  ======\n";
        cout << "======   replace index: " << replaceIndex << "   ======\n\n\n\n\n+_______________________________________________________\n";
        

        textFile[formattedIndex].word = posList[replaceIndex].word;
        textFile[formattedIndex].value = posList[replaceIndex].value;


        reviewReplaceIndex.push_back(formattedIndex); // adds the index of the replaced word in the review to the vector. used to print all the changed words at the end
    }


    return;
}

*/ // OCT 7 2023 1:49 PM




void initFormatted(vector<wordStruct>& formatted, vector<wordStruct> original) {
    for (int i = 0; i < original.size(); i++) { // sets formattedReview with all the originalReview elemets
        cout << ";;; before: " << formatted[i].word;
        formatted[i].word = original[i].word;
        formatted[i].value = original[i].value;
        cout << ";;; after : " << formatted[i].word;
    }

    for (auto i : formatted) { // ============== TESTING LINE =====================================================
        cout << i.word << " ";
    }
}



// finding total sentiment of wordstruct vector,
//   |  take in parameter of type wordstruct vector and return double that is the total
double totalSent(vector<wordStruct> review) {
    double total = 0.0;
    for (auto i : review) {
        total += i.value;
    }
    return total;
}




// will take in a word from wordstruct (string), and check if the final letter of that is actually a punct.
// will return the wordso that it can be readded to the vector; each word in the review will go through this to remove the punct
// INIT PUNCTUATION IN THE MAIN PROCCESSING FUNC
string removePunctuation(string word, vector<char>& punctuation) { // needs to call this in a "for each in formatted" to strip formatted of it's punct
    char tempPunct = word[word.size() - 1];
    if (ispunct(tempPunct) || !isalpha(tempPunct) && !isdigit(tempPunct)) { // if char is punctuation:
        //cout << "THE PUNCTUATION IS  " << tempPunct << "";
        //cout << "\neditstring1 is :  >>   " << editStr1;
        word.erase(word.end() - 1); // strip punctuation (final char) from the word
        //cout << "\neditstring1 is :  >>   " << editStr1 << endl << endl;
        

        // NEED TO STORE THE INDEX OF THE WORD THE PUNCTUATION IS AT. AFTER, HAVE A LOOP, FOR I, TACK ON PUNC CHAR AT VECTOR INDEX I THAT GOES TO WORD AT INDEX STORED IN VECTOR AT INDEX AT I
        //  |  changedIndex[i] is an index value. so, review[changedIndex[i]].word has the word that has punctuation.
        // //                                           BUT DOES IT HAVE PUNCT? WHAT IF IT DEOSNT HAVE PUNCT? JUST ADD THE INDEX TO A NEW VECTOR
        //                                                 well but if we have else : , temp punct pushback blank letter then it should work?
        //       |   review[changedIndex[i]].word += punctuation[i];   <==== would add punctuation back to word
        punctuation.push_back(tempPunct);
    }
    else {
        tempPunct = '#';
        punctuation.push_back(tempPunct); 
    }
    return word;
}




void replacePunctuation(vector<wordStruct>& formattedReview, vector<int> changedIndex, vector<char> punctuation) {
    for (int i = 0; i < formattedReview.size(); i++) { // for each word in the review
        if (punctuation[i] != '#') {
            cout << "<<<<<<< review[changedIndex[i]].word before punct edit: " << formattedReview[changedIndex[i]].word;
            formattedReview[changedIndex[i]].word += punctuation[i];
            cout << "<<<<<<< review[changedIndex[i]].word after  punct edit: " << formattedReview[changedIndex[i]].word;
        }
    }// end for
} // end replacePunctuation()



// takes in review and makes it lowercase so that the sentiment can be read
void lowercaseReview(vector<wordStruct>& formattedReview, vector<wordStruct> originalReview) { // this formatted review will be passed into all the other functions
    for (int i = 0; i < originalReview.size(); i++) { // for each element in the unedited review
        string word = originalReview[i].word; 
        for (int i = 0; i < word.length(); i++) { // for each char in the word

            if (isalpha(word[i])) { // if alpha, go lowercase
                word[i] = tolower(word[i]);
            }
        }// end for :: word's characters

        formattedReview[i].word = word; // sets the vector's word to be lowercase
    }// end for :: each in originalreview
} 



void reviewSentiment(vector<wordStruct> wordList, vector<wordStruct>& formattedReview, vector<wordStruct>& originalReview) { // initializes values for each element of the formattedReview, and then copies those values into original review 
    for (int i = 0; i < formattedReview.size(); i++) {

        int index = binarySearch(formattedReview[i].word, formattedReview, formattedReview.size(), 0); // finds index of currentWord in sentiment.txt 

        if (index != -1) { // IF BINARY SEARCH DOESNT FAIL
            //universalChangedIndex.push_back(index);  // will be used in printPos() & printNeg() ============================================================================================================================ , vector<int>& universalChangedIndex
            formattedReview[i].value = wordList[index].value; // sets the value to the same as the corresponding word in sentiment.txt
            originalReview[i].value = wordList[index].value; // does the same as above to the unedited vers of the word -- WILL BE USED IN printPos()/printNeg()
        }

    } // end for
}




void printReview(vector<wordStruct> originalReview) { // prints "formatted" review
    cout << "\nFORMATTED REVIEW:\n";
    int numChar = 0;
   
    for (int i = 0; i < originalReview.size(); i++) { // for each element in review
        while (numChar <= 80) { // while num of char in the line is less than 80
            string word = originalReview[i].word;

            if (word.length() + numChar <= 80) { // if the word won't be crossing the bounds of 80 char on the line
                
                for (int j = 0; j < word.length(); j++) { // for each char in word
                    cout << word[j];
                    numChar++;
                } // end for :: j
                
                cout << " ";
            }
            else {
                numChar = 81; // break while loop so a new line is entered
            }

            cout << "\n";
            numChar = 0;
        } // end while
    }// end for :: i
} // end printReview()



// NEED TO ADD IN THE PUNCTUATION AT THE END OF WORDS TOO. NEED TO PASS IN ORIGINAL. 
//   |  if i = replaceIndex[i], then cout formatted[i], otherwise cout original[i] 
//                                            |  if punctuation[i] != '#'?
void printPos(vector<wordStruct> formattedReview, vector<wordStruct> originalReview, vector<int>& changedIndex, vector<char> punctuation) { // prints the words updated to be more negative
    cout << "WORDS UPDATED TO BE MORE NEGATIVE: \n";
    for (int i = 0; i < formattedReview.size(); i++) { // for each word in the review
        if (originalReview[i].value > 1) { // if the original words needed to be replaced
            cout << right << setw(30) << originalReview[i].word << right  << setw(10) << originalReview[i].value;
            cout << right << setw(30) << formattedReview[i].word << right << setw(10) << formattedReview[i].value << "\n";
        }
    }
    
    // tack punctuation back onto word and call print review with the edited review 
    cout << "UPDATED REVIEW (MORE NEGATIVE):\n";
    replacePunctuation(formattedReview, changedIndex, punctuation);
    printReview(formattedReview);


    // call total sentimet
    cout << "\t\tUPDATED SENTIMENT: " << totalSent(formattedReview);
    changedIndex.clear(); // this is final function called, so need to clear the changed index for the next review
}


void printNeg(vector<wordStruct> formattedReview, vector<wordStruct> originalReview, vector<int>& changedIndex, vector<char> punctuation) {
    cout << "WORDS UPDATED TO BE MORE POSITIVE: \n";
    for (int i = 0; i < formattedReview.size(); i++) { // for each word in the review
        if (originalReview[i].value < -1) { // if the original words needed to be replaced
            cout << right << setw(30) << originalReview[i].word << right << setw(10) << originalReview[i].value;
            cout << right << setw(30) << formattedReview[i].word << right << setw(10) << formattedReview[i].value << "\n";
        }
    }

    // tack punctuation back onto word and call print review with the edited review
    cout << "UPDATED REVIEW (MORE POSITIVE):\n";
    replacePunctuation(formattedReview, changedIndex, punctuation);
    printReview(formattedReview);

    // call total sentimet
    cout << "\t\tUPDATED SENTIMENT: " << totalSent(formattedReview);
    changedIndex.clear(); // this is final function called, so need to clear the changed index for the next review
}



// replacing positive words in wordstruct vector (separate one for negative), printing out wordstruct vector, 
//   |  pass in wordstruct to overall replace func (not by reference, have it make a copy). go through both in order: replace neg, replace pos. 
//        |  inside those, pass by value the wordstruct vector. for each element, change the word to be neg/pos if it is >1. after for loop, call the total sentiment func and pass in the wordstruct vector

// ------ ------ ------ ------ ------ ------ ------ ------ 
void replacePos(vector<wordStruct> formattedReview, vector<wordStruct> originalReview, vector<wordStruct> negList, vector<int>& changedIndex, vector<char> punctuation) { // replaces the words that need to be more negative
    bool needsChange = false;
    int replaceIndex; // rand index for the pos/neg lists to replace words    
    
    for (int i = 0; i < formattedReview.size(); i++) { // for each in review, checks if the sentiment value is above 1.
        if (formattedReview[i].value > 1) {
            needsChange = true;
            replaceIndex = rand() % negList.size(); // rand number is the index the rand word will be

            formattedReview[i].word = negList[replaceIndex].word; // replaces word in review using rand index
            formattedReview[i].value = negList[replaceIndex].value; // replaces value as well

            changedIndex.push_back(i); // adds the index of the review's replaced word to a vector
        } // end if
    } // end for :: all in review vector

    if (!needsChange) { // if does not need change
        cout << "\nREVIEW NOT UPDATED. THE SENTIMENT REMAINS: " << totalSent(formattedReview) << "\n\n";
    }
    else {
        printPos(formattedReview, originalReview, changedIndex, punctuation); // prints the words changed from pos to negative
        cout << "UPDATED SENTIMENT : " << totalSent(formattedReview); // passes in the edited vector. since it's by value and not reference, it is not saved after it is passed in
    }

}

void replaceNeg(vector<wordStruct> formattedReview, vector<wordStruct> originalReview, vector<wordStruct> posList, vector<int>& changedIndex, vector<char> punctuation) {
    bool needsChange = false;
    int replaceIndex; // rand index for the pos/neg lists to replace words    

    for (int i = 0; i < formattedReview.size(); i++) { // for each in review, checks if the sentiment value is above 1.
        if (formattedReview[i].value < -1) {
            needsChange = true;
            replaceIndex = rand() % posList.size(); // rand number is the index the rand word will be

            formattedReview[i].word = posList[replaceIndex].word; // replaces word in review using rand index
            formattedReview[i].value = posList[replaceIndex].value; // replaces value as well

            changedIndex.push_back(i); // adds the index of the review's replaced word to a vector
        } // end if
    } // end for :: all in review vector

    if (!needsChange) { // if does not need change
        cout << "\nREVIEW NOT UPDATED. THE SENTIMENT REMAINS: " << totalSent(formattedReview) << "\n\n";
    }
    else {
        printPos(formattedReview, originalReview, changedIndex, punctuation); // prints the words changed from pos to negative
        cout << "UPDATED SENTIMENT : " << totalSent(formattedReview); // passes in the edited vector. since it's by value and not reference, it is not saved after it is passed in
    }

}
// ------ ------ ------ ------ ------ ------ ------ ------ 



void replace(vector<wordStruct> formattedReview, vector<wordStruct> originalReview, vector<wordStruct> posList, vector<wordStruct> negList, vector<int>& changedIndex, vector<char> punctuation) { // parent replace. will call the replace neg, and replace pos, respectively.  
    replacePos(formattedReview, originalReview, negList, changedIndex, punctuation);
    replaceNeg(formattedReview, originalReview, posList, changedIndex, punctuation);
}




// == declare  ==
// 
// __call order__
// init formatted
// lowercase
// remove punctuation
// review sentiment
// replace 
//    |  replace pos
//         |  print pos
//              |  print review
//              |  total sent
//    |  replace neg
//         |  print neg
//              |  print review
//              |  total sent



// helper functions above -----------------------------------------------------------








//===========================================================================================================================
//===========================================================================================================================
//===========================================================================================================================
//===========================================================================================================================
//===========================================================================================================================





//binary search finds the corresponding word in the sent list and adds that words' value to the vector's wordstruct word





int processReview(string fileName, vector<wordStruct> wordList, vector<wordStruct> posList, vector<wordStruct> negList) {
    ifstream inFile;
    inFile.open(fileName);
    if (!inFile.is_open()) {
        cout << "Review file: " << fileName << " invalid\n";
        return -1;
    }


    // == declare  ==
// 
// __call order__
// init formatted
// lowercase
// remove punctuation
// review sentiment
// replace 
//    |  replace pos
//         |  print pos
//              |  print review
//              |  total sent
//    |  replace neg
//         |  print neg
//              |  print review
//              |  total sent

    vector<wordStruct> originalReview, formattedReview;
    vector<char> punctuation; //  holds the punctuation that is stripped away
    vector<int> changedIndex; // holds the index of the words in the review that need to be changed
    wordStruct tempWord; // only used in initializing the review vector below

    while (inFile >> tempWord.word) { // initializing the review vector
        originalReview.push_back(tempWord);
    }

    initFormatted(formattedReview, originalReview); // initialize the secondary vector that will be edited
    
    for (auto i : formattedReview) { // for each value in the editable array, remove it's punctuation and add said punctuation to an array
        i.word = removePunctuation(i.word, punctuation);
    }

    reviewSentiment(wordList, formattedReview, originalReview);  // for each word in the review that is in sentiment.txt

    replace(formattedReview, originalReview, posList, negList, changedIndex, punctuation);







    // prev. %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // prev. %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // prev. %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // prev. %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // prev. %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // prev. %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // prev. %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // prev. %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // prev. %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // prev. %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // prev. %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // prev. %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    /*/

    double currentSent = 0; // for the current sent
    double totalSentiment = 0; // for total sent
    string str1;
    vector<wordStruct> formattedTextFile, originalTextFile;
    int index = 0;
    int formattedIndex = 0; // tracks the iteration the word loop is on ;; ie. tracks the current word's index in the input text file's vector
    vector<int> universalReplaceIndex; // index of word to be replaced (in the original file holding all the words and sentiment)
    vector<int> reviewReplaceIndex;    // index of word to be replaced in the review

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

        // ================================================================================== OCT 7 2:11 PM :: NEED TO ADD ALL WORDS TO A VECTOR FOR INFILE, SO THAT WE CAN MAKE COPIES LATER

        //if editstr has punctuation
        if (ispunct(tempPunct) || !isalpha(tempPunct) && !isdigit(tempPunct)) {
            //cout << "THE PUNCTUATION IS  " << tempPunct << "";
            //cout << "\neditstring1 is :  >>   " << editStr1;
            editStr1.erase(editStr1.end() - 1);
            //cout << "\neditstring1 is :  >>   " << editStr1 << endl << endl;
            wordHasPunct = true;
        }


        if (isalpha(editStr1[0])) { // if the string is a word
            index = binarySearch(editStr1, wordList, wordList.size(), 0); // finds index of word
            if (index != -1.0) { // IF BINARY SEARCH DOESNT FAIL
                if (wordList[index].value > 1 || wordList[index].value < -1) { // TESTING  IF STATEMENT; CAN BE REMOVED
                    cout << "\n++++++++++ : value :  " << wordList[index].value
                         << "\n++++++++++ : word  :  " << wordList[index].word << "\n";
                    cout << index << "\n\n";
                }
                universalReplaceIndex.push_back(index);
                
                totalSentiment += wordList[index].value;
            }
            //currentSent = originalSentiment(editStr1, wordList); // becasue we need to add the singular words' value to a struct, we have return value by itself to a variable
            //totalSentiment += wordList[index].value;
        }
        /*/
    /*
        if (wordHasPunct) {
            editStr1 += tempPunct; // fixes editstr1 to original state with it's punctuation
            wordHasPunct = false;
        }


        currentWord.word = editStr1;
        //cout << "\n%%%%%% > index: " << index;
        //cout << "\n%%%%%% > size : " << wordList.size() << "\n";
        if (index != -1) { */
            /*
            cout << "\n%%%%%%%%%%%%%%% > value of current word: " << currentWord.value;
            cout << "\n%%%%%%%%%%%%%%% >          current word: " << currentWord.word;
            cout << "\n%%%%%%%%%%%%%%% > value of wordlist[ind: " << wordList[index].value;
            cout << "\n%%%%%%%%%%%%%%% >          wordlist[wor: " << wordList[index].word;
            */

            //currentWord.value = wordList[index].value;
            
    /*
        }
        else { // if the binary search fails, set current value to default 0
            currentWord.value = 0;
        }
        /*//*
        cout << "\n\n ----  ----  ----  ----  ----  ----  ----";
        cout << "\n              AFTER CHANGE";
        cout << "\n ----  ----  ----  ----  ----  ----  ----";
        cout << "\n%%%%%%%%%%%%%%% > value of current word: " << currentWord.value;
        cout << "\n%%%%%%%%%%%%%%% >          current word: " << currentWord.word << "\n\n";
        */
    /*
            formattedTextFile.push_back(currentWord); // sets the formatted text file = text that is lowercase but otherwise untouched
            originalTextFile.push_back(currentWord);
            //replace(formattedTextFile, formattedIndex, posList, negList, reviewReplaceIndex);
            formattedIndex++;
        
    } // end while 



    // CALL OUTPUT FUNC  
    //outputFile(totalSentiment, originalTextFile, iter); // passes in the iteration var that's needed
    
    /*//*
    for (auto i : universalReplaceIndex) {
        cout << "\n~~~~~~~~~~~~~~\nREPLACE INDEX :  " << i;
        cout << "\n~~~~~~~~~~~~~~\nREPLACED WORD :  " << originalTextFile[i].word << "\n\n";
        
    }*/
/*
    

    for (auto i : originalTextFile) {
        cout << i.word << " ";
    }

    cout << "\n\nedited: \n";
    for (auto i : formattedTextFile) {
        cout << i.word << " ";
    }


    cout << "\n\n\n::::::::::::::::::::::::::::::::::::::::::::::::::\n";
    for (auto i : reviewReplaceIndex) {
        cout << "\nChanged index: " << i;
        cout << "\nChanged word: " << originalTextFile[i].word << "\n\n";
    }






    int posTotal, negTotal;
    
    cout << "ORIGINAL SENTIMENT: " << totalSentiment;

    cout << "\n\nWORDS UPDATED TO BE MORE POSITIVE:";
    for (int i = 0; i < formattedTextFile.size(); i++) {
        if (originalTextFile[i].value < -1) {
            cout << "\n" << originalTextFile[i].word << "   " << originalTextFile[i].value;
            cout << "\t\t\t" << formattedTextFile[i].word << "   " << formattedTextFile[i].value;
        }
    }

    cout << "\n\nWORDS UPDATED TO BE MORE NEGATIVE:";
    for (int i = 0; i < formattedTextFile.size(); i++) {
        if (originalTextFile[i].value > 1) {
            cout << "\n" << originalTextFile[i].word << "   " << originalTextFile[i].value;
            cout << "\t\t\t" << formattedTextFile[i].word << "   " << formattedTextFile[i].value;
        }
    }



    inFile.close();
    return 0;
}



/*//*
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
    }*/

    // prev. %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        // prev. %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        // prev. %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        // prev. %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        // prev. %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        // prev. %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%





    return 0;
}


// == BINARY SEARCH BASED OFF THE ITERATIVE VERSION MODELED BY GEEKSFORGEEKS.COM == 
int binarySearch(string str, vector<wordStruct> wordList, int high, int low) { // RETURNS INDEX IN TOTAL LIST OF EVERY WORD AND IT'S SENTIMENT
    while (low <= high) {
        int mid = low + (high - low) / 2;
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