//
// Created by Poyraz Güler on 20.12.2023.
//

#ifndef HW3_WORDITEM_H
#define HW3_WORDITEM_H


#include <string>
#include "DocumnetItem.h"
using namespace std;
struct WordItem {
    string word;
    vector<DocumentItem> doc_items;
    WordItem(string);
    void append(DocumentItem);
    string print();
};


#endif //HW3_WORDITEM_H
