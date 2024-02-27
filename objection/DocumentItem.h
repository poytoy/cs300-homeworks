//
// Created by Poyraz Güler on 21.11.2023.
//

#ifndef TREE_DOCUMENTITEM_H
#define TREE_DOCUMENTITEM_H
#include <string>
using namespace std;

struct DocumentItem{
    string documentName;
    int count;

    DocumentItem(const string& name, int c);
    void increase_count(){
        this->count=count+1;
    }
};


#endif //TREE_DOCUMENTITEM_H
