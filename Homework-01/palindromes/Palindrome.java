/*
   PURPOSE: This program reads a potential palindrome (text that is
   the same forwards as backwards) from the user and outputs a message
   indicating whether or not it is in fact a palindrome.

   DESIGN NOTES: The palindrome test is handled by isPalindrome, while
   all interaction is handled in main.
*/

import java.io.*;

public class Palindrome {

    /* isPalindrome
       ------------
         Tests a string for being a palindrome.

         INPUTS/PRECONDITIONS:
            word  is an arbitrary string to check.

         RESULTS/POSTCONDITIONS:
            returns true iff word is a palindrome (the same
               backwards and forwards)

         LIMITATIONS:
            The palindrome test does not ignore spaces, punctuation or
            capitalization.
    */
    public static boolean isPalindrome(String word)
    {
        int left  = 0;                  // Indexes of the leftmost and
        int right = word.length() - 1;  // rightmost unchecked character.

        // Check palindrome by moving left and right boundaries progressively
        // closer until they finally meet or pass each other.  Bail early
        // if we find a mismatch.
        while (left < right) {
            if (word.charAt(left) != word.charAt(right)) {
                return false;
            }

            --right;
            ++left;
        }

        // All the characters checked out.
        return true;
    }

    /* main
       ----

       Top-level function. Reads a potential palindrome from the
       user and yields a message indicating whether or not it is in
       fact a palindrome.

       INPUTS/PRECONDITIONS:
          args is the command-line arguments (unused)

       RESULTS/POSTCONDITIONS:
          None.
     */
    public static void main (String args[]) throws java.io.IOException {

        // getLine (below) requires a buffered stream, so...
        BufferedReader stdin =
            new BufferedReader( new InputStreamReader(System.in) );

        System.out.print("Enter possible palindrome: ");
        String line = stdin.readLine();
        if (isPalindrome(line)) {
            System.out.println("Yay, that's a palindrome!");
        } else {
            System.out.println("No, that's not a palindrome.");
        }
    }
}

