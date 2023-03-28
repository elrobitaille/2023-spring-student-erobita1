// Edgar Robitaille
// erobita1

#include <iostream>
#include <string> 
#include <fstream>
#include "language_model.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;

int main(int argc, char *argv[]) {
    // Check the second command line argument and do the corresponding action to the letter, similar to the midterm project.
    if (argc < 2) {
        cout << "Invalid argument list: f requires two additional command-line arguments" << endl;
        return 1; 
    }
    
    if (argc >= 2) {
        ifstream input_file(argv[1]);
        if (!input_file.is_open()) {
            cout << "Invalid file list: " << argv[1] << endl;
            return 1;
        }

        switch (*argv[2]) {
            case 'a':
                handle_a_command(input_file);
                break;
            case 'd':
                //handle_d_command();
                break;
            case 'c':
                //handle_c_command();
                break;
            case 'f':
                //handle_f_command();
                break;
            default: 
                cout << "Invalid command: valid options are a, d, c, and f" << endl;
                return 1;
        }      

        input_file.close();
    }

    
    
    return 0;
}