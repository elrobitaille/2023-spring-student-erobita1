// Edgar Robitaille
// erobita1

#include <iostream>
#include <string> 
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <cassert>
#include <sstream>
#include "model_tests.h"
#include "language_model.h"
#include <ios>

using std::cout;
using std::endl;
using std::string;
using std::pair;
using std::stringstream;
using std::ifstream;
using std::map;
using std::cerr;
using std::ios;

/* I believe that testing find_frequencies is sufficient for both handle_a_command and handle_d_command as they 
   only iterate through the results of find_frequencies with a for loop... so making sure that find_frequencies
   outputs correctly will ensure that a and d are functional as well.*/
bool test_find_frequencies() {
    ifstream input_file("tests.txt");
    map<string, int> expected_frequencies = {{"<START_1> <START_2> a", 1}, {"<START_2> a b", 1}, {"a b c", 2}, {"b c a", 1}, {"c a b", 1}, {"b c d", 1}, {"c d e", 1}, {"d e <END_1>", 1}, {"e <END_1> <END_2>", 1}};
    map<string, int> frequencies = find_frequencies(input_file);
    assert(frequencies == expected_frequencies);

    ifstream input_file1("tests1.txt");
    map<string, int> expected_frequencies1 = {{"<START_1> <START_2> aaaaaa", 1}, {"<START_2> aaaaaa bbbbbbbb", 1}, {"aaaaaa bbbbbbbb <END_1>", 1}, {"bbbbbbbb <END_1> <END_2>", 1}};
    map<string, int> frequencies1 = find_frequencies(input_file1);
    assert(frequencies1 == expected_frequencies1);

    ifstream input_file2("tests2.txt");
    map<string, int> expected_frequencies2 = {{"<START_1> <START_2> a", 1}, {"<START_2> a b", 1}, {"a b c", 1}, {"b c d", 2}, {"c d b", 1}, {"d b c", 1}, {"b c d", 1}, {"c d <END_1>", 1}, {"d <END_1> <END_2>", 1}};
    map<string, int> frequencies2 = find_frequencies(input_file2);
    assert(frequencies2 == expected_frequencies2);

    return true;
}

/* Just as handle_a/d_commands are dependent on find_frequencies, handle_c_command is dependent on 
   compare_trigrams, so this should sufficient for handle_c_command. */
bool test_compare_trigrams() {
    pair<string, int> pair1 = {"abc", 5};
    pair<string, int> pair2 = {"def", 3};
    bool expected_result = true;
    bool actual_result = compare_trigrams(pair1, pair2);
    assert(expected_result == actual_result);

    pair<string, int> pair3 = {"abc", 5};
    pair<string, int> pair4 = {"abc", 5};
    expected_result = false;
    actual_result = compare_trigrams(pair3, pair4);
    assert(expected_result == actual_result);

    pair<string, int> pair5 = {"abc", 5};
    pair<string, int> pair6 = {"bcd", 5};
    expected_result = true;
    actual_result = compare_trigrams(pair5, pair6);
    assert(expected_result == actual_result);

    return true;
}

bool test_handle_f_command() {
    ifstream input_file("tests.txt");

    if (!input_file.is_open()) {
        return false;
    }

    int result1 = handle_f_command(input_file, "a", "b");
    input_file.clear();
    input_file.seekg(0, ios::beg);
    int result2 = handle_f_command(input_file, "b", "c");
    
    input_file.close();

    if (result1 != 0 || result2 != 0) {
        return false;
    }

    ifstream input_file1("tests1.txt");

    if (!input_file1.is_open()) {
        return false;
    }

    int result3 = handle_f_command(input_file1, "a", "b");
    input_file1.clear();
    input_file1.seekg(0, ios::beg);
    int result4 = handle_f_command(input_file1, "aaaaaa", "bbbbbbbb");

    input_file1.close();

    if (result3 != 0 || result4 != 0) {
        return false;
    }

    ifstream input_file2("tests2.txt");

    if (!input_file2.is_open()) {
        return false;
    }

    int result5 = handle_f_command(input_file2, "a", "b");
    input_file2.clear();
    input_file2.seekg(0, ios::beg);
    int result6 = handle_f_command(input_file2, "b", "c");

    input_file2.close();

    if (result5 != 0 || result6 != 0) {
        return false;
    }

    return true;
}

int main(void) {
    // Run assertions to make sure that all tests worked and prints "All tests passed!"
    assert(test_handle_f_command());
    assert(test_find_frequencies());
    assert(test_compare_trigrams()); 
    cout << "All tests passed!" << endl;
    return 0;
}