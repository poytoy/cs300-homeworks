#include <iostream>
#include "AVLSearchTree.h"
#include "DocumentItem.h"
#include "WordItem.h"
#include "FileReaderFunc.h"
vector<string> parseAndLowercase(const std::string& line) {
    vector<string> word_list;
    istringstream iss(line);
    string word;

    while (iss >> word) {
        // Convert each character in the word to lowercase
        transform(word.begin(), word.end(), word.begin(), [](unsigned char c) { return std::tolower(c); });

        // Now 'word' contains the lowercase version of the word
       word_list.push_back(word);
    }
    return word_list;

}
int main() {
    int file_amount;
    string query_line;
    cout<<"Enter number of input files: ";
    cin>> file_amount;
    vector<string> filename_vector;
    for(int o=1;o<=file_amount;o++){
        string filename;
        cout<<"Enter "<<o<<". file name: ";
        cin>>filename;
        filename_vector.push_back(filename);
    }
    cin.clear();
    int loop=0;
    AVLSearchTree<string, WordItem > avl;
    for(int k=0;k<file_amount;k++){
        FileReaderFunc(filename_vector[k],avl);
    }
    vector<string>word_list;
    while(query_line!="ENDOFINPUT"){
    cout<<endl<<"Enter queried words in one line: ";

    // Read input until newline or EOF
    if(loop==0){
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');}
    std::getline(std::cin, query_line);



    if(query_line=="ENDOFINPUT"){
        break;
    }
    word_list=parseAndLowercase(query_line);
    if(word_list[0]=="remove"){
        avl.destroy_pub(word_list[1]);
        cout<<word_list[1]<<" has been REMOVED"<<endl;
    }
    else{
    //query
    string tb_printed_fr="";
    bool valid=true;
    for(int o=0;o<file_amount;o++){
        string tb_printed="in Document "+filename_vector[o]+",";
    for(int y=0;y<word_list.size();y++) {
        WordItem *Item_to_print = avl.search_pub(word_list[y]);
        if (Item_to_print != nullptr) {
            /* else {
            no_word_count++;
            if(no_word_count==word_list.size()){
                cout<<"No document contains the given query"<<endl;
            }
        }*/
       for(int u=0;u<Item_to_print->doc_items.size();u++){
           int not_in_count=0;
            if(Item_to_print->doc_items[u].documentName==filename_vector[o]){
                tb_printed+=" "+Item_to_print->word+" found "+ to_string(Item_to_print->doc_items[u].count+1)+" times,";
            }

       }}
        else{
        valid=false;}
    }

    if(tb_printed!="in Document "+filename_vector[o]+","){
        tb_printed.pop_back();
        tb_printed += ".";
        tb_printed_fr += tb_printed + "\n";
    }
    }
    if(valid==true){
    cout<<tb_printed_fr;}
    else{
        cout<<"No document contains the given query"<<endl;
    }
    }
    loop++;
    }
}
