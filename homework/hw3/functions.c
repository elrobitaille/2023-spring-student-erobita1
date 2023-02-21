#include "functions.h"

#include <stdio.h>
#include <string.h>

int read_file(FILE *fp, char words[][MAX_WORD_SIZE + 1], int size) {

  if (fp == NULL) {
    fprintf(stderr, "File not found"); 
    return 1;
  }

  while (fscanf(fp, "%s", words) != EOF) {
        printf("%s ", words);
    }


}

int match(const char *regex, const char *word, int restriction) {
  // TODO: Implement me!
  //match(ca*t, caaat)
  //match(a*t, aaat)
  //match()

  

}

