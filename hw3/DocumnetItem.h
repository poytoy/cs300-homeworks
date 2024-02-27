//
// Created by Poyraz Güler on 20.12.2023.
//

#ifndef HW3_DOCUMNETITEM_H
#define HW3_DOCUMNETITEM_H
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



#endif //HW3_DOCUMNETITEM_H
