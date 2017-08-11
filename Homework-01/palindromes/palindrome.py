#!/usr/bin/python

## PURPOSE: This program reads a potential palindrome (text that is
## the same forwards as backwards) from the user and outputs a message
## indicating whether or not it is in fact a palindrome.
##
## DESIGN NOTES: The palindrome test is handled by isPalindrome, while
## all interaction is handled in main.


## isPalindrome
## ------------
## Tests a string for being a palindrome.
##
## INPUTS/PRECONDITIONS:
##    word  is an arbitrary string to check.
##
## RESULTS/POSTCONDITIONS:
##    returns true iff word is a palindrome (same backwards and forwards)
##
## LIMITATIONS:
##    The palindrome test does not ignore spaces, punctuation or
##    capitalization.

def isPalindrome(word):
    left  = 0                           # Indexes of the leftmost and
    right = len(word) - 1               # rightmost unchecked character.

    # Check palindrome by moving left and right boundaries progressively
    # closer until they finally meet or pass each other.  Bail early if
    # we find a mismatch.
    while left < right:
        if word[left] != word[right]:
            return False
        
        left  = left + 1
        right = right - 1

    # If we made it to here, all the characters checked out.
    return True;



## Top-level code. Reads a potential palindrome from the user
## and yields a message indicating whether or not it is in fact a
## palindrome.
##
## INPUTS/PRECONDITIONS:
##    None.  (Command-line args, in sys.argv, are ignored).
##
## RESULTS/POSTCONDITIONS:
##    None.

line = raw_input('Enter possible palindrome: ')

if isPalindrome(line):
    print "Yay, that's a palindrome!"
else:
    print "No, that's not a palindrome."

