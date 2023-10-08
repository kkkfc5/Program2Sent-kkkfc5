// Kenneth Kakie  |  Oct. 8th 2023  |  Sentiment Analysis

#include "function.h"
#include "function.cpp"
#include <vector>
#include <string>

using namespace std;

int main() {

    vector<wordStruct> wordList, posList, negList;
    int returnVal = readSentimentFile(wordList, posList, negList);
    if (returnVal == -1) {
        exit(0);
    }

    ofstream outFile;

    outFile.open("reviewsPart1.txt"); // PURGES THE CONTENTS OF THE TEXT FILE
    outFile.close();

    outFile.open("reviewsPart1.txt", ios::app);

    //outFile << "\nwhy is this happening\n";
    // ^ this line exists because randomly random things break and just uncommenting it fixes it and I don;t know why I just really don't know why but I'm keeping it there regardless as a goodluck charm/ more convieninet to not have to keep typing it whenever I make a change

    for (int i = 1; i <= 8; i++) {
        string reviewFile = "review" + to_string(i) + ".txt";
        outFile << "PROCESSING FILE: " << reviewFile << "\n";
        outFile.close();
        returnVal = processReview(reviewFile, wordList, posList, negList);

        outFile.open("reviewsPart1.txt", ios::app);
        outFile << "\n\n\n\n\n\n\n\n\n";
    }

    outFile.close();
    //system("pause");
    return 0;
}





    // CURRENT ISSUES TO SOLVE 
    // 10/5/2023 7:13 AM
    // ------- Need to find the proper words to replace and actually replace them; the first one isn't replaceing properly
    //          needs to replace "amazing delicious loved wonderful enchanting"
    // //       straight from the index, call a func to decide if it is pos or neg 
    //
    // 10/5/2023 9:42 AM
    // need to find original unstripped versions and perserve capitalization
    // ------- need to  change sentiment check to be >1 <1 
    // need to keep punctuation after replacing word
    //       pass in char? and add char after word. if punct is false, then char = '\0' or ' '
    //       original check for this is unnecessary, I can delete it bc I'll be putting it through regardless?
    //              wrong, if im passing in char I don't need to delete
    // 
    // need to If no words were replaced, write that to the output file along with the original sentiment
    // output file lines must be less than or equal to 80 characters PER LINE, AND THEN PRINT
    // ------- get rid of global variable

    // 10/6/2023 9:39 AM
    // ------- NEED TO PASS IN THE REVIEWREPLACEINDEX VECTOR BY REFEENCE (&) to replace() AND THEN ADD THE ITERATION THE LOOP is on INTO THAT VECTOR TO STORE THE INDEX OF THE REPLACED WORD
    // ------- need to add the replaced words to a vector of wordstruct type, and then do a final final print where it prints replaced words and their sentiment.
    //          each of these wordstruct type values can be added to a single vector, and then in that final print, go through vector twice. If word replaced is pos, print.
    //              have corresponding vector of wordstruct type that uses same index to print the words before they were changed.
    //              or can do something special with % 2 and save change and unchanged
    //      is this to for the purpose of adding the punctuation to the words? 
    //       NO,| it's for listing which words have changed when printing at the end which words changed, so we don'nt need to store the changed words themselves, 
    //          | we just need to store the index of where they are
    // 
    // 10/7/2023 12:02 PM
    // MAKE FUNCTION TO TALLY TOTAL SENTIMENT AND RETURN IT 
    // NEED SEPARATE REPLACE FUNCTIONS FOR POS AND NEGATIVE?!?!?!
    //      so like: find original review. print it's sentiment.
    //               find words to update to more negative, then print the ones to be changed and whtat they are changed to. print updated reveiw, and updated sentiment sending in the newly negative wordstruct vector to the totalSentiment function.
    //               do the above wit pos as well.
    // to summarize:
    //      need function for : finding total sentiment of wordstruct vector, 
    //                            |  take in parameter of type wordstruct and return double that is the total
    //                          
    //                          replacing positive words in wordstruct vector (separate one for negative), printing out wordstruct vector, 
    //                            |  pass in wordstruct to overall replace func (not by reference, have it make a copy). go through both in order: replace neg, replace pos. 
    //                                 |  inside those, pass by value the wordstruct vector. for each element, change the word to be neg/pos if it is >1. after for loop, call the total sentiment func and pass in the wordstruct vector
    //                          
    //                          if there is punct then add call func to remove it and add removed punct word to the vector of changed words? 
    //                            |  Wouldn't need to keep words's index in the original text then if editing on the fly? Just keep running iteration tally, replace word at __ and keep global iteration
