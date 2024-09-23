/*
 * hasUniqueChars.c
 * 
 * Includes functions to check whether there are duplicate characters in any given string. Run that
 * function with hasUniqueChars. Note that this function fails if the string has any non-printing
 * characters. This file also has some helper functions and debug functions. 
 * 
 * Author: Gavin Davis
 */

#include <stdio.h>  // fprintf, printf
#include <stdlib.h> // exit() defined here
#include <string.h> // useful string operations
#include <ctype.h>  //useful character operations
#include <stdbool.h>  // to define a boolean type and true, false
                      // see https://en.wikibooks.org/wiki/C_Programming/stdbool.h

#include "binary_convert.h"

unsigned long makeBitMask(char chr);
bool checkCharInCheckbit(unsigned long bitmask, unsigned long checkBit);


/*
 * This function is for debugging by printing out the value
 * of an input insigned long as a binary string.
 */
void seeBits(unsigned long value, char *debug_text) {
  
  // string to represent binary value of variable value
  char *bin_str;

  bin_str = ulong_to_bin_str(value);
  printf("%s%s\n", debug_text, bin_str);
  free(bin_str);
  
}


/*
 * Given an input string of chars, check for any non-printing
 * characters and print an error and exit if the string has any.
 */
void checkInvalid(char * inputStr) {
  char nextChar;
  int i;
  
  for(i = 0; i < strlen(inputStr); i++) {
    nextChar = inputStr[i];

    // if nextChar is invalid (31 or less or 127 as an ascii char code), then bail out
    if ((nextChar <= 31 ) || (nextChar == 127)) {
      fprintf(stderr, "invalid character in string\n");
      exit(EXIT_FAILURE);
    }
  }
}


/*
 * This function takes in a string, and returns true if there are no repeated characters in the string.
 * It returns false if there are any duplicate characters.
 * This function fails if the passed string has any non-printing characters in it.
 */
bool hasUniqueChars(char * inputStr) {
  // bail out quickly if any invalid characters
  checkInvalid(inputStr);
  
  int i;   // loop counter
  
  unsigned long checkBitsexcl_amp = 0;  // for checking ! though @ 
  unsigned long checkBitsA_z = 0;   // for checking A through z and {|}~

  char nextChar;         // next character in string to check

  // -------------------------------------------------------------

  char bit_mask_char; // the index of the char at 
  unsigned long bitmask; // the bitmask for the character
  
  for(i = 0; i < strlen(inputStr); i++) {
    nextChar = inputStr[i];
    //printf("nextChar is %c, with ASCII value %d \n",nextChar,nextChar);

    // check exclamation -> at (that's an at not an ampersand bro)
    if(nextChar >= 33 && nextChar <= 64) {
      nextChar = nextChar - 33; // change it to be the index we care about

      bitmask = makeBitMask(nextChar); // make the bit vector for that character

      // check if the index of the current character is already in the bit checker
      if(checkCharInCheckbit(bitmask, checkBitsexcl_amp)) {
        // if it is, return false
        return false;
      }
      else {
        // otherwise, we can run bitwise OR to only add a 1 in the slot the bitmask has
        checkBitsexcl_amp = checkBitsexcl_amp | bitmask;
      }

    }

    // check A -> z
    else if(nextChar >= 65) {   // this is the same shit as above but with a different offset & checkbit
      nextChar = nextChar - 65;

      // make our bitmask - defined below
      bitmask = makeBitMask(nextChar);

      // check if the index of the current character is already in the bit checker
      if(checkCharInCheckbit(bitmask, checkBitsA_z)) {
        // if it is, it's not a unique string
        return false;
      }
      else {
        // otherwise, we can run bitwise OR to only add a 1 in the slot the bitmask has
        checkBitsA_z = checkBitsA_z | bitmask;
      }
    }
    
    else{
      // the character is a space and you can ignore it
      // can afford to ignore non-printing because checkInvalid already accounts for that
    }
  }

  // if through all the characters, then no duplicates found
  return true;
  
}

/*
  Makes a bitmask (bit vector) for the given char. 
  Returns a long with 0's in every slot except the value of the passed character.

  Using the logic that 2^chr should be a long with only a 1 in the slot associated
  with the number. Would use math.h library for exponents but I couldn't figure out
  how to compile it well so I just built my own power function.
*/
unsigned long makeBitMask(char chr) {
  // printf("making bitmask for: %c, which has ASCII value %d \n", chr, chr);

  unsigned long ret_long = 1;
  for(int i = 0; i < chr; i++) {
    ret_long *= 2;
  }
  // printf("that bitmask is: %s \n", ulong_to_bin_str(ret_long));

  return ret_long;
}


/* 
  Checks whether the bitmask overlaps with the given bit vector.
*/
bool checkCharInCheckbit(unsigned long bitmask, unsigned long checkBit) {
      // if there's a 1 in the correct slot for both of them, we've already seen that character
      if(( checkBit & bitmask) == bitmask) {
        return true;
      }
      else {
        return false;
      }
}