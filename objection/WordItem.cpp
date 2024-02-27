//
// Created by Poyraz Güler on 21.11.2023.
//

#include "WordItem.h"
#include <iostream>
using namespace std;
#include <string>
WordItem::WordItem(string word):word(word){
}
void WordItem::append(DocumentItem doc_it){
    doc_items.push_back(doc_it);
}
string WordItem::print(){
    for(int i=0;i<doc_items.size();i++){
        return " "+word+" found "+ to_string(doc_items[i].count+1)+" times,";
    }
}