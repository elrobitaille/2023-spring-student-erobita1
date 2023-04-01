// Edgar Robitaille
// erobita1

#include <iostream>
#include <string> 
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <iterator>
#include <utility>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::map;
using std::pair;
using std::vector;
using std::cerr;


/* Helper function that creates a hashmap/dictionary of the words in each file with their number of occurences. */
map<string, int> find_frequencies(ifstream& input_file) {
    map<string, int> word_frequency;

    string word;
    while (input_file >> word) {
        /* Create a new file stream for the inner files and make sure that the file is open and valid. */
        int print_placeholders = 1; // Decides whether or not <START> and <END> placeholders are printed. 
        ifstream inner_file(word);
        if (!inner_file.is_open()) {
            print_placeholders = 0;
            cerr << "Invalid file: " << word << endl;
        } 

        /* Create the strings that mark the beginning and end of a file. */
        string start1 = "<START_1>", start2 = "<START_2>";
        string end1 = "<END_1>", end2 = "<END_2>";

        /* Set the starter words as the START_1 and START_2 strings. */
        if (print_placeholders) { // Checks if print is necessary for <START> and <END>. 
            string prev_word1 = start1, prev_word2 = start2; 
            string current_words;    

            /* Iterate through the dictionary and update the frequencies as well as the contained words. */
            while (inner_file >> word) {
                current_words = prev_word1 + " " + prev_word2 + " " + word;
                word_frequency[current_words] += 1;
                prev_word1 = prev_word2;
                prev_word2 = word;
            }

            /* Add the END_1 and END_2 portions to the end trigrams. */
            current_words = prev_word1 + " " + prev_word2 + " " + end1;
            word_frequency[current_words] += 1;
            current_words = prev_word2 + " " + end1 + " " + end2;
            word_frequency[current_words] += 1;
            
        }
        
        inner_file.close();
    }

    return word_frequency; // Return the dictionary with appropriate frequencies. 
}

bool compare_trigrams(const pair<string, int>& first_pair, const pair<string, int>& second_pair) {
    /* Compare the frequencies of each pair. */
    if (first_pair.second != second_pair.second) {
        return first_pair.second > second_pair.second;
    /* If frequencies are the same then compare based on alphabetical order. */
    } else if (first_pair.first != second_pair.first) {
        return first_pair.first < second_pair.first;
    /* If frequencies and the pairs are the same, return false. */
    } else if (first_pair.second == second_pair.second && first_pair.first == second_pair.first) {
        return false;   
    }
    return true; // If no conditions are met 
}

int handle_a_command(ifstream& input_file) {
    /* Make sure that the file is open and is valid. */
    if (!input_file.is_open()) {
        return 1;
    }

    /* Create a new hashmap and call find_frequencies function as a helper to get frequencies. */
    map<string, int> word_hashmap;
    word_hashmap = find_frequencies(input_file);

    /* Iterate through the hashmap and write in the format # - [WORD 1 WORD 2 WORD 3] in ASCENDING order.
       Note that this is based on the ASCII of the first word, then goes through second and third words
       if the compared characters are the same. < comes before upper or lower case letters, and upper  
       case comes before lower case in this ascending order. */
    for (const auto& trigram : word_hashmap) {
        cout << trigram.second << " - [" << trigram.first << "]" << endl;
    }

    return 0;
}

int handle_d_command(ifstream& input_file) {
    /* Make sure that the file is open and is valid. */
    if (!input_file.is_open()) {
        return 1;
    }
    
    /* Create a new hashmap and call find_frequencies function as a helper to get frequencies. */
    map<string, int> word_hashmap;
    word_hashmap = find_frequencies(input_file);

    /* Iterate through the hashmap and write in the format # - [WORD 1 WORD 2 WORD 3] in DESCENDING order.
       Note that this is based on the ASCII of the first word, then goes through second and third words
       if the compared characters are the same. < comes after upper or lower case letters, and upper  
       case comes after lower case in this descending order. */
    for (auto reverse_iterator = word_hashmap.rbegin(); reverse_iterator != word_hashmap.rend(); ++reverse_iterator) {
        cout << reverse_iterator->second << " - ["  << reverse_iterator->first << "]" << endl;
    }
    
    return 0;
}

int handle_c_command(ifstream& input_file) {
    /* Make sure that the file is open and is valid. */
    if (!input_file.is_open()) {
        return 1;
    }

    /* Create a new hashmap and call find_frequencies function as a helper to get frequencies. */
    map<string, int> word_hashmap;
    word_hashmap = find_frequencies(input_file);

    /* Create a vector that contains a word pair, iterates from beginning to end of hashmap. */
    vector<pair<string, int>> word_vector(word_hashmap.begin(), word_hashmap.end());

    /* Uses sort function and compare_trigrams helper function to sort the list by descending numbers and
       then alphabetical order if the frequency is the same value. */
    sort(word_vector.begin(), word_vector.end(), compare_trigrams);

    /* Iterate through the hashmap and write in the format # - [WORD 1 WORD 2 WORD 3] in DESCENDING 
       numerical order. Note that the dictionary has been sorted numerically so it will be based on 
       frequency first, then go based on alphabetical order if they have the same frequency. This
       is the same for loop from handle_a_command. */ 
    for (const auto& trigram : word_vector) {
       cout << trigram.second << " - [" << trigram.first << "]" << endl; 
    }
    
    return 0;
}

int handle_f_command(ifstream& input_file, const string& first_word, const string& second_word) {
    /* Make sure that the file is open and is valid. */
    if (!input_file.is_open()) {
        return 1;
    }

    /* Create a new hashmap and call find_frequencies function as a helper to get frequencies. */
    map<string, int> word_hashmap;
    word_hashmap = find_frequencies(input_file);

    /* String for first two trigram sequence, the matched trigram, and its frequency. */
    string combined_string = first_word + " " + second_word;
    int freq_num = 0;
    string result_trigram; 

    for (const auto& trigram : word_hashmap) {
        /* Check first if the string matches the searched string (combined strings of first and second word). */
        if (trigram.first.find(combined_string) == 0) { 
            // Check if the frequency of the trigram is greater or alphabetical ordering. 
            if (freq_num < trigram.second || (freq_num == trigram.second && trigram.first < result_trigram)) {
                /* Update the frequency freq_num with the current trigram's  
                   frequency and update result_trigram with the updated current 
                   trigram. */ 
                freq_num = trigram.second;
                result_trigram = trigram.first;
            }
        }
    }

    /* Format outputting matched trigram or lack of a matched trigram. */
    if (!result_trigram.empty()) {
        cout << freq_num << " - [" << result_trigram << "]" << endl; 
    } else {
        cout << "No trigrams of the form [" << first_word << " " << second_word << " ?]" << endl;
    }

    return 0;
}