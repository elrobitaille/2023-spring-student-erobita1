//Edgar Robitaille
//erobita1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

#define MAX_WORD_NUM 1024
#define MAX_INPUT_SIZE 128
#define DEFAULT_RESTRICTION 10

int main(int argc, const char *argv[]) {
  char words[ MAX_WORD_NUM ][ MAX_WORD_SIZE + 1 ]; 
  int size = MAX_WORD_NUM;

  /* Check if there is a correct number of arguments when running the program, 2 or 3 depending if there is a restriction.*/
  if (argc != 2 && argc != 3) {
    fprintf(stderr, "Wrong number of arguments\n");
    return 1;
  }

  /* Read the file and check if the file has a valid path or address. If not, catch error. */
  FILE *input_file = fopen(argv[1], "r");
  if (input_file == NULL) {
    fprintf(stderr, "Error opening file\n");
    return 1;
  }

  int num_words = read_file(input_file, words, MAX_WORD_NUM); //Check if there is an issue in functions.c.

  if (num_words != 0) {
    fprintf(stderr, "Error in functions.c");
  }

  int restriction_length = DEFAULT_RESTRICTION; 
  if (argc == 3) {
    restriction_length = atoi(argv[2]); // Set restriction length from the command line argument, utilize atoi from stdlib.h.
  }

  fclose(input_file); //Close the input file.

  return 0;
}
