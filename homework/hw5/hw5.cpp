// Edgar Robitaille
// erobita1

#include <iostream>
#include <string> 
#include <fstream>
#include <vector>
#include <map>
#include "language_model.h"


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::map;
using std::vector;
using std::cerr;

int main(int argc, char *argv[]) {
    // Check the second command line argument and do the corresponding action to the letter, similar to the midterm project.
    if (argc <= 2) {
        cerr << "Invalid command: valid options are a, d, c, and f" << endl;
        return 1; 
    }
    
    /* Account for the case where there is the correct # of command line arguments. */
    if (argc > 2) {
        // Check that file is properly opened. 
        ifstream input_file(argv[1]);
        if (!input_file.is_open()) {
            cerr << "Invalid file list: " << argv[1] << endl;
            return 1;
        }

        // Switch case to account for each command type and make sure command char is valid. 
        switch (*argv[2]) {
            case 'a':
                handle_a_command(input_file);
                break;
            case 'd':
                handle_d_command(input_file);
                break;
            case 'c': 
                handle_c_command(input_file);
                break;
            case 'f':
                if (!argv[3] || !argv[4]) {
                    cerr << "Invalid argument list: f requires two additional command-line arguments" << endl;
                    return 1; 
                }
                handle_f_command(input_file);
                break;
            default: 
                cerr << "Invalid command: valid options are a, d, c, and f" << endl;
                return 1;
        }      

        input_file.close();
    }

    
    
    return 0;
}