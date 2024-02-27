//
// Created by Poyraz Güler on 24.11.2023.
//

#ifndef TREE_FILEREADERFUNC_H
#define TREE_FILEREADERFUNC_H
#include <string>
#include "AVLSearchTree.h"
#include "WordItem.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include "DocumentItem.h"
using namespace std;
#include <sstream>
void fileOpen(string path,vector<string>& words) {

    ifstream file(path);

    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string word;
            while (iss >> word) {
                word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalpha(c); }), word.end());

                // Convert to lowercase
                transform(word.begin(), word.end(), word.begin(), ::tolower);
                words.push_back(word);
            }
        }
        file.close();
    } else {
        cout<<"error";
    }
}
void FileReaderFunc(string fileName,AVLSearchTree<string,WordItem>& avl) {
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
        WordItem* existingWordItemPtr=avl.search_pub(word);
        if (existingWordItemPtr!= nullptr) {
            WordItem* existingWordItem = avl.search_pub(word);
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
        }
            else {
                // If the word doesn't exist, create a new WordItem
                WordItem *wordItem = new WordItem(word);
                wordItem->append(d);

                // Insert the new WordItem into the AVLSearchTree

                avl.insert_pub(word, wordItem);
            }

        }



#endif //TREE_FILEREADERFUNC_H
}