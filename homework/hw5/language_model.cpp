// Edgar Robitaille
// erobita1

#include <iostream>
#include <string> 
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;

int handle_a_command(ifstream& input_file) {
    if (!input_file.is_open()) {
        return 1;
    }

    string word;
    while (input_file >> word) {
      cout << word << endl;
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