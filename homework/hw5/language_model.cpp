// Edgar Robitaille
// erobita1

#include <iostream>
#include <string> 
#include <fstream>
#include <unordered_map>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::unordered_map;

int handle_a_command(ifstream& input_file) {
    if (!input_file.is_open()) {
        return 1;
    }

    unordered_map<string, int> word_frequency;

    string word;
    while (input_file >> word) {
        ifstream inner_file(word);
        if (!inner_file.is_open()) {
            cout << "Invalid file: " << word << endl;
        } 

        while (inner_file >> word) {
            word_frequency[word] += 1;
        }

        inner_file.close();
    }
    
    return 0;
}

int handle_d_command(void) {
    
    return 0;
}

int handle_c_command(void) {
    
    return 0;
}

int handle_f_command(void) {
    
    return 0;
}