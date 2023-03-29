// Edgar Robitaille
// erobita1

#include <iostream>
#include <string> 
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::unordered_map;
using std::pair;
using std::vector;
using std::cerr;

unordered_map<string, int> find_frequencies(ifstream& input_file) {
    unordered_map<string, int> word_frequency;

    string word;
    while (input_file >> word) {
        ifstream inner_file(word);
        if (!inner_file.is_open()) {
            cerr << "Invalid file: " << word << endl;
        } 

        while (inner_file >> word) {
            word_frequency[word] += 1;
        }

        inner_file.close();
    }
    return word_frequency;
}

int handle_a_command(ifstream& input_file) {
    if (!input_file.is_open()) {
        return 1;
    }

    unordered_map<string, int> word_hashmap;
    word_hashmap = find_frequencies(input_file);

    vector<string> three_words;
    string start1 = "<START_1>", start2 = "<START_2>";
    string end1 = "<END_1>", end2 = "<END_2>";

    three_words.push_back(start1);
    three_words.push_back(start2);
    

    return 0;
}

int handle_d_command(ifstream& input_file) {
    if (!input_file.is_open()) {
        return 1;
    }
    
    unordered_map<string, int> word_hashmap;

    word_hashmap = find_frequencies(input_file);
    
    return 0;
}

int handle_c_command(ifstream& input_file) {
    if (!input_file.is_open()) {
        return 1;
    }

    unordered_map<string, int> word_hashmap;

    word_hashmap = find_frequencies(input_file);
    
    return 0;
}

int handle_f_command(ifstream& input_file) {
    if (!input_file.is_open()) {
        return 1;
    }

    unordered_map<string, int> word_hashmap;

    word_hashmap = find_frequencies(input_file);

    return 0;
}