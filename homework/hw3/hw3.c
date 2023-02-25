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

  /* Check if there is a correct number of arguments when running the program, 2 or 3 depending if there is a restriction.*/
  if (argc != 2 && argc != 3) {
    fprintf(stderr, "Wrong number of arguments\n");
    return -1;
  }

  /* Read the file and check if the file has a valid path or address. If not, catch error. */
  FILE *input_file = fopen(argv[1], "r");
  if (input_file == NULL) {
    fprintf(stderr, "Error opening file\n");
    return -1;
  }

  int num_words = read_file(input_file, words, MAX_WORD_NUM); //Check if there is an issue in functions.c.


  /* If the number of words is zero or less, there is an issue in functions.c. */
  if (num_words <= 0) {
    fprintf(stderr, "Error in functions.c\n");
    return -1;
  }

  /* Setting default restriction length as 10. */
  int restriction_length = DEFAULT_RESTRICTION; 
  if (argc == 3) {
    restriction_length = atoi(argv[2]); // Set restriction length from the command line argument, utilize atoi from stdlib.h.
  }

  /* Call the match function to see if matches regex pattern. */
  for (int i = 0; i < num_words; i++) {
    if (match(argv[1], words[i], restriction_length)) {
      printf("%s\n", words[i]);
    }
  }

  /* Create a list to read the regex character from the user. */
  char regex[MAX_INPUT_SIZE];
  int valid_match = 1;

  /* Gathers the regex expression from the user, then print corresponding matches to the pattern.*/
  while (valid_match == 1) {
   valid_match = fscanf(stdin, "%s", regex);
    if (valid_match != 1) {
      break;
    }

    /* Iterate through the words array and print out the matching patterns by calling match. */
    int foundMatch = 0;
    int validMatch = 0;
    for (int i = 0; i < num_words; i++) {
      if (match(regex, words[i], restriction_length)) {
        printf("%s\n", words[i]);
        foundMatch = 1;
        validMatch = 1;
      }
    }
    /* If no match is found, print no match. */
    if (!foundMatch) {
      fprintf(stdout, "No match found for regex \'%s\'\n", regex);
      validMatch = 1;
    }
    if (validMatch) {
      continue;
    }
  }

  fclose(input_file); //Close the input file 

  return 0;
}