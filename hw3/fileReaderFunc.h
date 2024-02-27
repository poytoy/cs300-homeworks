//
// Created by Poyraz Güler on 21.12.2023.
//

#ifndef HW3_FILEREADERFUNC_H
#define HW3_FILEREADERFUNC_H
#include <string>
#include "bst.h"
#include "WordItem.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include "DocumnetItem.h"
using namespace std;
#include <sstream>
void fileOpen(string path, vector<string>& words) {
    ifstream file(path);

    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string word;
            while (iss >> word) {
                std::string processedToken;

                for (char c : word) {
                    if (isalpha(c)) {
                        processedToken += tolower(c);
                    } else {
                        // Treat non-alphabetic characters as word separators
                        if (!processedToken.empty()) {
                            words.push_back(processedToken);
                            processedToken.clear();
                        }
                    }
                }
                if (!processedToken.empty()) {
                    words.push_back(processedToken);
                }
            }  // Correct placement of the inner while loop closing brace
        }
        file.close();
    } else {
        cout << "error";
    }
}
void FileReaderFunc(string fileName,BSTSearchTree<string,WordItem>& bst,HashTable &hashTable) {
    vector<string> words;
    //get on desktop of the file
    const char *desktopPath = getenv("HOME");
    if (desktopPath == nullptr) {
        cerr << "Error getting desktop path" << endl;
        // or handle the error in another way
    }

    fileOpen(/*string(desktopPath) + "/Desktop/" + */fileName, words);
    for (int i = 0; i < words.size(); i++) {
        DocumentItem d(fileName, 0);
        string word = words[i];
        WordItem *existingWordItemPtr = bst.search_pub(word);
        if (existingWordItemPtr != nullptr) {
            WordItem *existingWordItem = bst.search_pub(word);
            // If the word already exists, append the DocumentItem to it
            //if the word has the document item appended just increase the count
            //else ad the new document item
            bool check = 0;
            for (int i = 0; i < existingWordItem->doc_items.size(); i++) {
                if (existingWordItem->doc_items[i].documentName == fileName) {
                    existingWordItem->doc_items[i].increase_count();
                    check = 1;
                }
            }
            if (check == 0) { existingWordItem->append(d); }
        } else {
            // If the word doesn't exist, create a new WordItem
            WordItem *wordItem = new WordItem(word);
            wordItem->append(d);

            // Insert the new WordItem into the AVLSearchTree
            hashTable.insert(wordItem);
            bst.insert_pub(word, wordItem);
        }

    }
}


#endif //HW3_FILEREADERFUNC_H
