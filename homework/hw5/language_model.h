// Edgar Robitaille
// erobita1

#include <string>
#include <unordered_map>
#ifndef LANGUAGE_MODEL_H
#define LANGUAGE_MODEL_H

std::unordered_map<std::string, int> find_frequencies(std::ifstream& input_file);
int handle_a_command(std::ifstream& input_file);
int handle_d_command(std::ifstream& input_file);
int handle_c_command(std::ifstream& input_file);
int handle_f_command(std::ifstream& input_file);

#endif 