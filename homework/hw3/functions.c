#include "functions.h"

#include <stdio.h>
#include <string.h>

int read_file(FILE *fp, char words[][MAX_WORD_SIZE + 1], int size) {

  /* Check if the file is null, leading to an error if nothing inside. */
  if (fp == NULL) {
    fprintf(stderr, "File not found\n"); 
    return -1;
  }

  /* Check the number of words in the file, if not equal to 1, there is an error. */
  int word_count = 0;
  if (fscanf(fp, "%d", &word_count) != 1) {
        fprintf(stderr, "Invalid input file format\n");
        return -1;
    }

  /* If the word count is less than zero or greater than the size, results in an error. */
  if (word_count < 0 || word_count > size) {
    fprintf(stderr, "Error: Invalid word count\n");
    return -1;
  }

  int i = 0;
  while (i < word_count)  {
    /* Iterate through file and make sure input is valid by checking size of fscanf. */
    if (fscanf(fp, "%s", words[i]) != 1) {
      fprintf(stderr, "Error, Invalid input file format\n");
      return -1;
    }
    /* Make sure the number of words does not exceed the max word size. */
    if (strlen(words[i]) > MAX_WORD_SIZE) {
      fprintf(stderr, "Error, too many words in input file\n");
      return -1;
    }
    i++;
  }

  return 0; 

}

int match(const char *regex, const char *word, int restriction) {
  // TODO: Implement me!
  //match(ca*t, caaat)
  //match(a*t, aaat)
  //match()

  

}

