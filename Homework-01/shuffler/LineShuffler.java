/*
   LineShuffler.java
   =================

   PURPOSE:
   This class stores a sequence of lines and retrieves them in random order.

   When run as a program, it reads a sequence of lines from the user,
   terminated by an empty line and the prints out those lines in random order.

*/

import java.util.*;
import java.io.*;

public class LineShuffler {

    //
    // CONSTRUCTORS
    //

    /* LineShuffler
       ------------
       Initializes the object to empty.

       INPUTS/PRECONDITIONS:  None.

       OUTPUTS/POSTCONDITIONS:
          The object will contain no lines (isEmpty() == true).
     */
    LineShuffler() {
        count_ = 0;
        rnd_   = new Random();
        lines_ = new Vector<String>();
    }

    //
    // METHODS
    //

    /* removeLine
       ----------
       Removes and returns a random line stored in the LineShuffler.

       INPUTS/PRECONDITIONS:
          The object should be non-empty (i.e., isEmpty() == false).

       OUTPUT/POSTCONDITIONS:
          Returns one of the strings previously stored, and removes
              that copy of the string from the object.
    */
    String removeLine() {
        int index = rnd_.nextInt(count_);
        --count_;
        return (String) lines_.remove(index);
    }

    /* addLine
       -------
       Adds a line to the collection stored in the LineShuffler.

       INPUTS/PRECONDITIONS:
          line  is an arbitrary string.

       OUTPUT/POSTCONDITIONS:
          line  has been added to the collection.
    */
    void addLine(String line) {
        lines_.add(line);
        ++count_;
    }

    /* isEmpty
       -------
       Tests whether there are strings in this collection.

       INPUTS/PRECONDITIONS:
          None.

       OUTPUTS/POSTCONDITIONS:
          Returns true iff there are no lines in the LineShuffler.
    */
    boolean isEmpty() {
        return count_ == 0;
    }

    //
    // PRIVATE DATA
    //

    int    count_;                      // Number of lines stored.
    Random rnd_;                        // State of random number generator.
    Vector<String> lines_;              // Collection (array) of lines.


    //
    // STATIC METHODS
    //

    /* main
       ----
         Program entry point.  Reads lines from standard input (terminated
         by a blank line) and outputs them to standard output in
         random order.

       INPUTS/PRECONDITIONS:
          args is the command-line arguments (unused)

       OUTPUTS/POSTCONDITIONS:
          None.
    */
    public static void main (String args[]) throws java.io.IOException {
        // getLine (below) requires a buffered stream, so...
        BufferedReader stdin =
            new BufferedReader( new InputStreamReader(System.in) );

        // Read in the lines.
        System.out.println("Enter lines to shuffle, ending with a blank line");
        LineShuffler randomLines = new LineShuffler();
        for (;;) {
            String line = stdin.readLine();
            if (line.equals("")) {
                break;
            }
            randomLines.addLine(line);
        }

        // Display the shuffled lines.
        System.out.println("Here are the shuffled lines:");
        while(!randomLines.isEmpty()) {
            System.out.println(randomLines.removeLine());
        }
    }

}
