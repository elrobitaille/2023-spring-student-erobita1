// Edgar Robitaille
// erobita1

/* This header has the declarations for functions in language_model.cpp for the basic operations 
of the trigram language model. */

#include <iostream>
#include <string> 
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <iterator>

#ifndef LANGUAGE_MODEL_H
#define LANGUAGE_MODEL_H

// Create a hashmap and find frequencies of the trigrams
std::map<std::string, int> find_frequencies(std::ifstream& input_file);
// Compare each trigram based on their frequency and alphabetical order
bool compare_trigrams(const std::pair<std::string, int>& first_pair, const std::pair<std::string, int>& second_pair);
// Handles 'a' to print all the trigrams in ascending order. 
int handle_a_command(std::ifstream& input_file);
// Handles 'd' to print all the trigrams in descending order. 
int handle_d_command(std::ifstream& input_file);
// Handles 'c' to print all the trigrams in descending numerical order. 
int handle_c_command(std::ifstream& input_file);
// Handles 'f' to search for a specific trigram. 
int handle_f_command(std::ifstream& input_file, const std::string& first_word, const std::string& second_word);

#endif 