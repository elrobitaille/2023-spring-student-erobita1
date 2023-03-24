// Edgar Robitaille
// erobita1

#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
    // Check the second command line argument and do the corresponding action to the letter, similar to the midterm project.
    if (argc < 2) {
        cout << "Invalid argument list: f requires two additional command-line arguments" << endl;
        return 1; 
    }
    
    if (argc == 3) {
        switch (*argv[1]) {
            case 'a':
                //handle_a_command();
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
    }
    
    return 0;
}