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

#ifndef LANGUAGE_MODEL_H
#define LANGUAGE_MODEL_H

std::map<std::string, int> find_frequencies(std::ifstream& input_file);
int handle_a_command(std::ifstream& input_file);
int handle_d_command(std::ifstream& input_file);
int handle_c_command(std::ifstream& input_file);
int handle_f_command(std::ifstream& input_file, const std::string& first_word, const std::string& second_word);

#endif 