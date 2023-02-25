//Edgar Robitaille
//erobita1
#include <assert.h>
#include <stdio.h>

#include "functions.h"

#define TEST_RESTRICTION_1 10
#define TEST_RESTRICTION_2 2
#define TEST_RESTRICTION_3 5
#define TEST_RESTRICTION_4 30

#define MAX_WORD_NUM 1024

//Edgar Robitaille
//erobita1

void test_read_files() {
  FILE* fptr = fopen("test_file_1.txt", "w");
  fprintf(fptr, "5\nintermediate\ninttterrmeediateeee\nprogram\nppproograaamm\naaa");
  fclose(fptr);
}

void test_match_regex() {
  /* No special regex characters cases. */
  assert(match("abc", "abc", TEST_RESTRICTION_1) == 1);
  assert(match("abcd", "abc", TEST_RESTRICTION_1) == 0);
  assert(match("", "", TEST_RESTRICTION_1) == 1);
  assert(match("abcd", "abc", TEST_RESTRICTION_1) == 0);
  assert(match("abc", "abcd", TEST_RESTRICTION_1) == 0);
  assert(match("abc", "bc", TEST_RESTRICTION_1) == 0);
  assert(match("aaaaaaa", "aaa", TEST_RESTRICTION_1) == 0);
  assert(match("aaa", "aaaaaaa", TEST_RESTRICTION_1) == 0);
}

void test_match_regex_star() {
  /* Tests with star regex character.*/
  assert(match("abcd*", "abc", TEST_RESTRICTION_1) == 1);
  assert(match("abc*d", "abcccccccd", TEST_RESTRICTION_1) == 1);
  assert(match("abc*de", "abcccccccd", TEST_RESTRICTION_1) == 0);
  assert(match("ab*cd", "abcd", TEST_RESTRICTION_1) == 1);
  assert(match("ab*cd", "accd", TEST_RESTRICTION_1) == 0);
  assert(match("a*", "aaaaaa", TEST_RESTRICTION_1) == 1);
  assert(match("a*", "bbbb", TEST_RESTRICTION_1) == 0);
  assert(match("aaa*b*bb", "aaaabbbbbb", TEST_RESTRICTION_1) == 1);
}

void test_match_regex_question() {
  /* Cases with question mark regex character. */
  assert(match("a?", "", TEST_RESTRICTION_1) == 1);
  assert(match("a?", "b", TEST_RESTRICTION_1) == 0);
  assert(match("a?", "a", TEST_RESTRICTION_1) == 1);
  assert(match("ab?", "a", TEST_RESTRICTION_1) == 1);
  assert(match("ab?", "ab", TEST_RESTRICTION_1) == 1);
  assert(match("ab?", "abc", TEST_RESTRICTION_1) == 0);
  assert(match("ab?", "abc", TEST_RESTRICTION_1) == 0);
  assert(match("ab?", "ab", TEST_RESTRICTION_1) == 1); 
  assert(match("a?b?", "ab", TEST_RESTRICTION_1) == 1);  
  assert(match("a?b?", "", TEST_RESTRICTION_1) == 1);  
}

void test_match_regex_tilde() {
  assert(match("~", "aaaa", TEST_RESTRICTION_1) == 1);
  assert(match("~", "", TEST_RESTRICTION_1) == 1);
  assert(match("~", "a", TEST_RESTRICTION_1) == 1);
  assert(match("~~", "aaaa", TEST_RESTRICTION_1) == 1);
  assert(match("~", "abcdefghijk", TEST_RESTRICTION_1) == 0);
  assert(match("~", "abcdefghij", TEST_RESTRICTION_1) == 1);
  assert(match("~bc", "bbc", TEST_RESTRICTION_1) == 1);
  assert(match("~bc", "abcd", TEST_RESTRICTION_1) == 0);
  assert(match("~~a~~", "bbbbbaaa", TEST_RESTRICTION_1) == 1);
  assert(match("~~a~~b~~c~~", "xaxxbxxc", TEST_RESTRICTION_1) == 1);
  assert(match("a~", "abcdefghij", TEST_RESTRICTION_1) == 1);
  assert(match("a~", "abcdefghijklm", TEST_RESTRICTION_1) == 0);
}

void test_match_regex_multiple() {
  assert(match("!2*keK?ee?rCC?C*aP?E*eR*T*", "!2222keKerCCCaeRRRT",
               TEST_RESTRICTION_1) == 1);
  assert(match("!~2*keK?ee?rCC?C*aP?E*eR*T*", "!2222keKerCCCaeRRRT",
               TEST_RESTRICTION_1) == 1);
  assert(match("~abc", "sda12!$2", TEST_RESTRICTION_1) == 0);
  assert(match("~a~bc*d?", "sssa12bcccccc", TEST_RESTRICTION_1) == 1);
}

void test_match_regex_tilde_restriction() {
  
}

int main() {
  printf("Starting Tests...\n");
  
  test_read_files();
  test_match_regex();
  test_match_regex_star();
  test_match_regex_question();
  test_match_regex_tilde();
  test_match_regex_multiple();
  test_match_regex_tilde_restriction(); 
  printf("All tests passed!!!\n");
}
