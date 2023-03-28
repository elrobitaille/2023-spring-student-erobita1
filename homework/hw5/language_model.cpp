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

int handle_a_command(string input_file) {
    ifstream inner_file(input_file);
    if (!inner_file.is_open()) {
        return 1;
    }

    string line;
    while (getline(inner_file, line)) {
        cout << line << endl;
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