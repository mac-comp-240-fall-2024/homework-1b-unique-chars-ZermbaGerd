/*
 * Tests the functions in hasUniqueChars.c

Author: Gavin
 */

#include <stdio.h>    // printf
#include <stdbool.h>  // to define a boolean type and true, false
#include <string.h>   // strcpy  to copy a string
#include <assert.h>


// declaration of function from hasUniqueChars.c
bool hasUniqueChars(char * inputStr);


int main() {

  // ------------------------------------------------------------

  char string3[128];   // can copy in up to 127 characters
                       // chose 128 because it is a multiple of 8 bytes

  hasUniqueChars(string3);
  // -------------------------------------------------------------
  // Thorough and exhaustive tests of hasUniqueChars()  
  
  bool ok;    // holds the result of hasUniqueChars(); used in asserts
  
  // Test 1: should fail, because of duplicated characters
  strcpy(string3, "This should fail (l and s and i and h)");
  ok = hasUniqueChars(string3);
  assert(!(ok));
  
  // Test 2: This should be true and not fail
  strcpy(string3, "abcdefghij");
  ok = hasUniqueChars(string3);
  assert(ok);

  // Test 3: Tests all printable characters - should succeed
  strcpy(string3, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$^&*()_+-={}[]|:;<>,.?/~");
  ok = hasUniqueChars(string3);
  assert(ok);
  
  // Test 4: Testing multiple spaces & edge characters - should fail
  strcpy(string3, "~~aa     !!!!");
  ok = hasUniqueChars(string3);
  assert(!ok);


  // Test that it gives an error when given non-printing characters
  strcpy(string3, "a b cc\n");
  ok = hasUniqueChars(string3);

  strcpy(string3, "a b cc\r");
  ok = hasUniqueChars(string3);

  strcpy(string3, "a \0 b cc\n");
  ok = hasUniqueChars(string3);
  
  return 0;
}