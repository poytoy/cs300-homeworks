#include <iostream>
#include "bst.h"
#include "WordItem.h"
#include "hashTable.h"
#include "fileReaderFunc.h"
vector<string> parseAndLowercase(const std::string& line) {
    vector<string> word_list;
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
                    word_list.push_back(processedToken);
                    processedToken.clear();
                }
            }
        }
        if (!processedToken.empty()) {
            word_list.push_back(processedToken);
        }
    }
    return word_list;
}
const double HashTable::loadFactorThreshold = 0.8;
const std::size_t HashTable::initialCapacity = 1000;
int main() {
    int file_amount;
    string query_line;
    cout << "Enter number of input files: ";
    cin >> file_amount;
    vector<string> filename_vector;
    for (int o = 1; o <= file_amount; o++) {
        string filename;
        cout << "Enter " << o << ". file name: ";
        cin >> filename;
        filename_vector.push_back(filename);
    }
    cin.clear();

    BSTSearchTree<string, WordItem> bst;
    HashTable hsh;
    for (int k = 0; k < file_amount; k++) {
        FileReaderFunc(filename_vector[k], bst, hsh);
    }
    hsh.final();
    vector<string> word_list;

    cout << endl << "Enter queried words in one line: ";

    // Read input until newline or EOF

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, query_line);

    double BSTTime_s;
    double HTTime_s;
    word_list = parseAndLowercase(query_line);
        for(int a=0;a<2;a++){
        string tb_printed_fr="";
        bool valid=true;
        for(int o=0;o<file_amount;o++){
            string tb_printed="in Document "+filename_vector[o]+",";
            bool doc_valid=true;
            for(int y=0;y<word_list.size();y++) {
                int k = 100;
                auto start = std::chrono::high_resolution_clock::now();
                WordItem *Item_to_print=nullptr;
                if(a==0){
                for(int i=0;i<k;i++){
                Item_to_print = bst.search_pub(word_list[y]);}
                auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
                BSTTime_s= BSTTime.count() / k;}
                if(a==1){for(int i=0;i<k;i++){
                Item_to_print = hsh.get(word_list[y]);
                auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
                HTTime_s=HTTime.count() / k;}}
                if(Item_to_print == nullptr){valid=false;}
                if (Item_to_print != nullptr) {
                    bool word_found_in_doc=false;
                    /* else {
                    no_word_count++;
                    if(no_word_count==word_list.size()){
                        cout<<"No document contains the given query"<<endl;
                    }
                }*/
                    for(int u=0;u<Item_to_print->doc_items.size();u++){
                        if(Item_to_print->doc_items[u].documentName==filename_vector[o]){
                            tb_printed+=" "+Item_to_print->word+" found "+ to_string(Item_to_print->doc_items[u].count+1)+" times,";
                            word_found_in_doc=true;
                        }
                    }
                if(!word_found_in_doc){
                    doc_valid=false;
                    break;
                }
                }

            }

            if(doc_valid){
                tb_printed.pop_back();
                tb_printed += ".";
                tb_printed_fr += tb_printed + "\n";
            }
        }
        if(valid){
            cout<<tb_printed_fr;}
        else{
            cout<<"No document contains the given query"<<endl;
        }
    }
    cout <<"Time: "<<to_string(BSTTime_s)<<endl;
    cout<<"Time: "<<to_string(HTTime_s)<<endl;

    cout<<"Speed Up: "<<BSTTime_s/HTTime_s;
}




//implement a version where both hsh and bst are searched





