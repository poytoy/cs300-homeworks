//
// Created by Poyraz Güler on 21.11.2023.
//

#ifndef WORDITEM_HEADER
#define WORDITEM_HEADER
#include <string>
#include "DocumentItem.h"
using namespace std;
struct WordItem {
    string word;
    vector<DocumentItem> doc_items;
    WordItem(string);
    void append(DocumentItem);
    string print();
};

#endif // WORDITEM_HEADER
