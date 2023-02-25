//Edgar Robitaille
//erobita1
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

  /* Code to check if first number in file is invalid and less than number of total words in file. */
  int new_count = 0;
  for (int i = 0; i < strlen(words); i++) {
    if (words[i+1] != NULL && strcmp(words[i], "\n") != 0 && strcmp(words[i], "\0") != 0) {
      new_count += 1;
    }
  }

  /* If it is invalid, the number will be less than the number of words in the file. */
  if (new_count < word_count) {
    fprintf(stderr, "Error with first number in file\n");
  }

  printf("%d : %d", new_count, word_count);

  
  return word_count;  /* Return the word count of the file, showing that read_file successfully ran. */

}

int match(const char *regex, const char *word, int restriction) {
  /* This is the base case for regex. If both word and regex are empty then they are a match, return 1. */
  if (*regex == '\0' && *word == '\0') {
    return 1;
  /* No match if regex is empty while the word isn't, return 0. */
  } else if (*regex == '\0' && *word != '\0') {
    return 0;
  }
  
  /* Checks if the next character is the special regex character *. */
  if (*(regex+1) == '*') {
    /* Checks if current character matches character preceding asterisk, or that it is a ? regex character. */
    if (*word == *regex || *regex == '?') {
      /* If true, recursively calls match and uses next character as a starting point.
         If this condition fails, then it recursively calls again and skips +2 characters 
         because +1 has already been taken care of in the earlier i statement  */
      if (match(regex, word + 1, restriction)) {
        return 1;
      }  
    }
    return (match(regex + 2, word, restriction)); 
  }

  /* Checks if the next character is the special regex character ?. */
  if (*(regex + 1) == '?') {
    if (*word == *regex || *regex == '?') {
      if (match(regex + 2, word + 1, restriction)) {
        return 1;
        }  
    }
      return (match(regex + 2, word, restriction)); 
    }

  /* Checks if the next character is the special regex character ~. */
  if (*regex == '~') {
    int new_restriction = restriction;
    /* Add restriction value to the restriction space if there are successive ~ special characters. */
    while (*++regex == '~') {
        new_restriction += restriction;
    }
    for (int i = 0; i <= new_restriction; i++) {
        if (match(regex, word + i, new_restriction - i)) {
            return 1;
        }
        /* For cases to prevent overload past end of array bound, stop when reaching the null terminator. */
        if (word[i] == '\0') {
            return 0;
        }
    }
    return 0;
  }

  /* If the words are equal, recursively call match to show that they are the same. */
  if (*regex == *word) {
    return match(regex+1, word+1, restriction);
  }
  
  return 0; // No match was reached, return 0. 
}


