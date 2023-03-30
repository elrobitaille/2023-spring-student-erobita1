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

        vector<string> three_words;
        string start1 = "<START_1>", start2 = "<START_2>";
        string end1 = "<END_1>", end2 = "<END_2>";

        string prev_word1 = start1, prev_word2 = start2; 
        string current_words;    

        while (inner_file >> word) {
            current_words = prev_word1 + " " + prev_word2 + " " + word;
            word_frequency[current_words] += 1;
            prev_word1 = prev_word2;
            prev_word2 = word;
        }

        current_words = prev_word1 + " " + prev_word2 + " " + end1;
        word_frequency[current_words] += 1;
        current_words = prev_word2 + " " + end1 + " " + end2;
        word_frequency[current_words] += 1;

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

    for (const auto& trigram : word_hashmap) {
        cout << trigram.second << " - [" << trigram.first << "]" << endl;
        //cout << trigram.first[0] << endl;
    }

    

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

    for (const auto& trigram : word_hashmap) {
        cout << trigram.second << " - [" << trigram.first << "]" << endl;
    }
    
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